#include "includes.h"

Vector3 CAimbot::GetHitbox(Entity entity)
{
	if (entity.m_entity_type.IsPlayer())
	{
		switch (g_pAimbotSettings->m_hitbox->get_selected())
		{
			case 0:		return entity.m_visual_state.GetHead();
			case 1:		return entity.m_visual_state.GetChest();
		}
	}
	else if (entity.m_entity_type.IsVehicle())
	{
		return entity.m_entity.GetVehicle().GetDriverHead(entity.m_entity_type.GetPrint(), entity.m_visual_state);
	}

	return { };
}

Vector3 CAimbot::CalculateAngle(Vector3 to, Vector3 from)
{
	if (to.Zero() || from.Zero())
	{
		return { };
	}

	auto difference = to - from;

	difference.Normalize();

	Vector3 inaccuracy = m_local.m_visual_state.GetInaccuracy();

	Vector3 angle_out = {	
		atan2f(difference.x, difference.z) + atan2f(inaccuracy.x, inaccuracy.z),
		atan2f(difference.y, sqrtf((difference.x * difference.x) + (difference.z * difference.z))) + inaccuracy.y,
		0.f
	};

	return angle_out;
}

float CAimbot::GetTimeToTarget(Entity entity, Vector3 hitbox)
{
	auto mag_type	= m_local.m_active_weapon.GetMuzzleState().GetMagazine().GetMagazineType();
	auto weap_type	= m_local.m_active_weapon.GetWeaponType();

	float initial_speed = mag_type.GetInitialSpeed() > weap_type.GetInitialSpeed() ? mag_type.GetInitialSpeed() : weap_type.GetInitialSpeed();
	float distance = m_local.GetGunPosition().Distance(hitbox);

	/* every 0.05 seconds the game updates bullets so we use that as our simultation step */
	float delta_time = 0.05f;
	Vector3 speed = Vector3(1.f, 0.f, 0.f) * initial_speed * 1.f;

	Vector3 bullet_pos = m_local.GetGunPosition();
	float total_time = 0.f;

	while (true)
	{
		/* calculate the amount the bullet has moved since the last tick */
		Vector3 segment = speed * delta_time;
		bullet_pos = bullet_pos + segment;

		/* update speed to take into account air friction and gravity */
		Vector3 acceleration = speed * (speed.size() * mag_type.GetAmmoType().GetAirFriction());
		acceleration.y -= mag_type.GetAmmoType().GetGravityCoef() * G_CONST;

		speed = speed + acceleration * delta_time;

		if (bullet_pos.x > distance)
		{
			break;
		}

		total_time += delta_time;
	}

	return total_time;
}

/* anton codenz */
float CAimbot::CalculateAngle(float rad)
{
	float initial_speed = m_local.m_active_weapon.GetMuzzleState().GetMagazine().GetMagazineType().GetInitialSpeed() > m_local.m_active_weapon.GetWeaponType().GetInitialSpeed() ? m_local.m_active_weapon.GetMuzzleState().GetMagazine().GetMagazineType().GetInitialSpeed() : m_local.m_active_weapon.GetWeaponType().GetInitialSpeed();

	Vector2 V(
		cosf(rad) * initial_speed,
		sin(rad) * initial_speed
	);

	Vector2 A_grav = Vector2(0, -G_CONST);
	Vector2 bPos = Vector2(0, 0);
	float time = 0.f;

	while (time < m_local.m_active_weapon.GetMuzzleState().GetMagazine().GetMagazineType().GetAmmoType().GetTimeToLive())
	{
		float dTime = 0.005f;

		Vector2 A_neg = V * V.size() * m_local.m_active_weapon.GetMuzzleState().GetMagazine().GetMagazineType().GetAmmoType().GetAirFriction();

		V = V + ((A_neg + A_grav) * dTime);

		bPos = bPos + V * dTime;

		time += dTime;

		if (bPos.y < 0.f)
		{
			return bPos.x;
		}
	}

	return FLT_MAX;
}

/* anton codenz */
float CAimbot::step(float wDist)
{
	float ang = 0.001f;

	int i = 0;

	while (true) {
		i++;

		float range = CalculateAngle(ang);

		if (ang > 0.707f) {
			return FLT_MAX;
		}


		if (range == FLT_MAX) {
			return FLT_MAX;
		}

		if (range > wDist) {
			return ang;
		}

		if (i == 10000) {
			return FLT_MAX;
		}

		ang += 0.001f;
	}

	return 0.f;
}

Vector3 CAimbot::GetDistanceTravelled(Entity entity, Vector3 hitbox, Vector3 angle, float distance)
{
	auto mag_type = m_local.m_active_weapon.GetMuzzleState().GetMagazine().GetMagazineType();
	auto weap_type = m_local.m_active_weapon.GetWeaponType();

	float initial_speed = mag_type.GetInitialSpeed() > weap_type.GetInitialSpeed() ? mag_type.GetInitialSpeed() : weap_type.GetInitialSpeed();

	/* every 0.005 seconds the game updates bullets so we use that as our simultation step */
	float delta_time = 0.005f;
	Vector3 speed = angle * initial_speed * 1.f;

	Vector3 distance_travelled = { };
	float total_time = 0.f;

	do
	{	/* calculate the amount the bullet has moved since the last tick */
		Vector3 segment = speed * delta_time;
		distance_travelled = distance_travelled + segment;

		/* update speed to take into account air friction and gravity */
		Vector3 acceleration = speed * (speed.size() * mag_type.GetAmmoType().GetAirFriction());
		acceleration.y -= mag_type.GetAmmoType().GetGravityCoef() * G_CONST;

		speed = speed + acceleration * delta_time;

		total_time += delta_time;

		if (total_time > mag_type.GetAmmoType().GetTimeToLive())
		{
			return Vector3{ };
		}

	} while (distance_travelled.x < distance);

	distance_travelled.z = total_time;

	return distance_travelled;
}

void CAimbot::handle_smoothing(Vector3& ang, Entity ent, const clock_t begin)
{
	if (g_pAimbotSettings->m_smoothing->get() > 0.f)
	{
		float delta_time = float(clock() - begin) / CLOCKS_PER_SEC;

		if (delta_time > 5.f)
		{
			delta_time = 0.01f;
		}

		if (ent.m_entity.GetAddress().as<UINT_PTR>() != m_last_aim_ent.GetAddress().as<UINT_PTR>())
		{
			curr_time = 0.01f;
		}

		max_time = g_pAimbotSettings->m_smoothing->get();

		if (curr_time > max_time)
		{
			curr_time = max_time;
		}

		curr_time += delta_time;

		float percent = curr_time / max_time;

		Vector3 viewang = m_local.GetViewangles();

		if (max_time > 0.f && curr_time > 0.f)
		{
			Vector3 delta = ang - viewang;

			if (delta.x > IM_PI)
			{
				delta.x -= 2 * IM_PI;
			}
			else if (delta.x < -IM_PI)
			{
				delta.x += 2 * IM_PI;
			}

			delta = (delta * percent);

			ang = viewang + delta;
		}
	}
}

Vector3 CAimbot::CalculatePosition(Entity entity)
{
	auto hitbox_pos = this->GetHitbox(entity);

	Vector3 distance_travelled	= { };
	Vector3 current_angle = { 1.f, 0.f, 0.f };
	Vector3 gun_pos = g_pClient->m_camera.GetPosition();
	float distance = gun_pos.Distance(hitbox_pos);

	distance_travelled = this->GetDistanceTravelled(entity, hitbox_pos, current_angle, distance);

	auto speed = (entity.m_visual_state.GetVelocity() - m_local.m_visual_state.GetVelocity()) + (m_local.m_visual_state.GetAcceleration());

	hitbox_pos.x += speed.x * distance_travelled.z;
	hitbox_pos.y += speed.y * distance_travelled.z;
	hitbox_pos.z += speed.z * distance_travelled.z;

	float distance_2d = Vector2(hitbox_pos.x - gun_pos.x, hitbox_pos.z - gun_pos.z).size();

	float zeroing_angle = step(300.f);
	float target_angle = step(distance_2d);

	if (zeroing_angle == FLT_MAX || target_angle == FLT_MAX)
	{
		return { };
	}

	hitbox_pos.y += (tanf(target_angle - zeroing_angle) * distance_2d);

	g_pClient->m_camera.WorldToScreen(hitbox_pos, m_pred);

	return hitbox_pos;
}

Entity CAimbot::GetClosesetEntity(Vector3& angle_out)
{
	float distance			= FLT_MAX;
	Entity out_entity		= { };

	auto entities = g_pClient->m_world.GetEntities();

	for (auto& entity : g_pClient->m_world.GetEntities())
	{
		/* error checking */

			/* entity error checking */
		if (!entity.GetAddress() || entity.IsDead() || entity.IsObjectHidden() ||

			/* keep target error checking */
		   (!m_find_new_target && entity.GetAddress().as<UINT_PTR>() != m_last_aim_ent.GetAddress().as<UINT_PTR>())

			)
		{
			continue;
		}

		auto ent = Entity(entity);

		ent.m_visual_state = entity.GetFutureVisualState();

		if (ent.m_visual_state.GetOrigin().Zero())
		{
			continue;
		}

		ent.m_entity_type = entity.GetEntityType();

		/*if (ent.m_entity_type.IsVehicle())
		{
			auto veh = Vehicle(entity.GetVehicle());

			if (!veh.m_driver.m_entity.GetAddress() || veh.m_driver.m_entity.IsDead())
			{
				continue;
			}

			if ((veh.m_driver.m_entity.GetTeam() == m_local.m_local.GetTeam()) && g_pAimbotSettings->m_ignore_team->active())
			{
				continue;
			}
		}
		else
		{
			if ((ent.m_entity.GetTeam() == m_local.m_local.GetTeam()) && g_pAimbotSettings->m_ignore_team->active())
			{
				continue;
			}
		}*/

		auto angle = CalculateAngle(GetHitbox(ent), m_local.GetGunPosition());

		if (!m_find_new_target && entity.GetAddress().as<UINT_PTR>() == m_last_aim_ent.GetAddress().as<UINT_PTR>())
		{
			/* so we can keep aimbotting target out of fov */

			angle_out = angle;
			return ent;
		}

		float dist = m_local.GetViewangles().Distance(angle);

		if (dist < distance && dist < (g_pAimbotSettings->m_fov->get() / 360.f))
		{
			distance = dist;
			out_entity = ent;
			angle_out = angle;
		}
	}

	return out_entity;
}

bool CAimbot::think()
{
	if (g_pAimbotSettings->m_enabled->active() && g_pAimbotSettings->m_key->IsActive())
	{
		start_time = clock();

		m_local = g_pClient->m_local;

		m_local.Update();

		m_last_aim_ent.Update();

		if (!m_last_aim_ent.GetAddress() || m_last_aim_ent.IsDead())
		{
			m_last_aim_ent = A3Entity{ };
			m_find_new_target = true;
			curr_time = { };
		}

		Vector3 angle = { };

		auto ent = GetClosesetEntity(angle);

		if (angle.x == 0.f || angle.y == 0.f)
		{
			m_pred = { };
			curr_time = { };

			return false;
		}

		angle = CalculateAngle(CalculatePosition(ent), g_pClient->m_world.IsThirdperson() ? m_local.GetGunPosition() : g_pClient->m_camera.GetPosition());

		if (angle.x == 0.f || angle.y == 0.f)
		{
			m_pred = { };
			curr_time = { };

			return false;
		}

		if (!g_pAimbotSettings->m_only_visualize->active())
		{
			m_local.Update();

			handle_smoothing(angle, ent, start_time);

			m_local.SetViewangles(angle);
		}

		m_last_aim_ent = ent.m_entity;

		m_find_new_target = false;

		return true;
	}
	else
	{
		m_find_new_target = true;
		m_pred = { };
		curr_time = { };
	}

	return false;
}