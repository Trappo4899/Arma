#include "includes.h"

A3Entity::A3Entity()
{
	m_address = nullptr;
	m_data = { };
}

A3Entity::A3Entity(Address address)
{
	m_address = address;

	m_data = { };

	if (m_address)
	{
		m_data = m_address.at<entity_data_t>();
	}
}

void A3Entity::Update()
{
	m_data = m_address.at<entity_data_t>();
}

Address A3Entity::GetAddress()
{
	return m_address;
}

VisualState A3Entity::GetCurrentVisualState()
{
	return VisualState(m_address.at(Offsets::Entity::CurrentVisualState));
}

VisualState A3Entity::GetFutureVisualState()
{
	return VisualState(m_address.at(Offsets::Entity::FutureVisualState));
}

EntityType A3Entity::GetEntityType()
{
	return EntityType(m_address.at(Offsets::Entity::EntityType));
}

EntityType A3Entity::GetClassType()
{
	return EntityType(m_address.at(Offsets::Entity::ClassType));
}

RealPlayer A3Entity::GetRealPlayer()
{
	return RealPlayer(m_address.at(Offsets::Entity::RealPlayer));
}

bool A3Entity::IsDead()
{
	return m_data.IsDead;
}

UINT32 A3Entity::GetNetworkID()
{
	return m_data.NetworkID;
}

Weapon A3Entity::GetActiveWeapon()
{
	int index = abs((m_data.WeaponIndex + m_data.WeaponIndex) * 4);

	return Weapon(m_address.at(Offsets::Entity::WeaponTable).as(index * 5));
}

UINT32 A3Entity::GetWeaponListSize()
{
	return m_data.WeaponListSize;
}

bool A3Entity::IsHoldingItem()
{
	return m_data.WeaponIndex != 255;
}

A3Vehicle A3Entity::GetVehicle()
{
	return A3Vehicle(this->GetAddress());
}

int A3Entity::GetHealth()
{
	return (1.f - m_address.at(Offsets::Entity::Dammage).at<float>()) * 100.f;
}

void A3Entity::HideObject()
{
	/* as long as the value is can be & 1 the object will be hidden*/
	m_address.set<BYTE>(Offsets::Entity::ObjectHidden, 131);
}

bool A3Entity::IsObjectHidden()
{
	return m_data.ObjectHidden & 1;
}

void A3Entity::ChangeCollision(A3Entity target, Address localObject)
{
	target.GetAddress().set<UINT64>(Offsets::Entity::Collision, localObject.as<UINT64>());
}

bool A3Entity::IsCollisionEnabled(A3Entity target, Address localObject)
{
	return target.GetAddress().as<UINT64>(Offsets::Entity::Collision) == localObject.as<UINT64>();
}

UINT32 A3Entity::GetTeam()
{
	return m_data.Team;
}

Entity::Entity()
{
	m_entity = { };
	m_visual_state = { };
	m_entity_type = { };
}

Entity::Entity(A3Entity entity)
{
	m_entity = entity;
}

bool Entity::Update()
{
	m_visual_state			= m_entity.GetFutureVisualState();

	if (m_visual_state.GetOrigin().Zero())
	{
		return false;
	}

	m_distance				= g_pClient->m_parent.GetCurrentVisualState().GetOrigin().Distance(m_visual_state.GetOrigin());
	m_health				= m_entity.GetHealth();

	m_stance				= (ENTITY_STANCE)m_entity_type.GetMovesType().GetMoveInfo(m_visual_state.GetMoveInfoTableIndex1()).GetActionMap().GetActionID();

	m_invisible				= m_entity.IsObjectHidden();

	if (m_entity.IsHoldingItem())
	{
		m_active_weapon = m_entity.GetActiveWeapon();
	}

	return g_pVisuals->GetBox(*this, m_box);
}

A3Vehicle::A3Vehicle()
{
	m_address = nullptr;
}

A3Vehicle::A3Vehicle(Address address)
{
	m_address = address;
	m_data = m_address.at<entity_data_t>();
}

bool A3Vehicle::HasDriver()
{
	return m_address.at(Offsets::Entity::DriverEntityLink);
}

A3Entity A3Vehicle::GetDriver()
{
	return A3Entity(m_address.at(Offsets::Entity::DriverEntityLink));
}

Vector3 A3Vehicle::GetDriverHead(const std::string& vehName, VisualState visState)
{
	auto driver = this->GetDriver();

	if (!driver.GetAddress() || driver.IsDead())
	{
		return Vector3{ };
	}

	if (head_positions.contains(vehName))
	{
		return Math::model_to_world(head_positions.at(vehName), visState.GetInverseRotationMatrix(), visState.GetOrigin());
	}

	return Vector3{ };
}

Vehicle::Vehicle()
{
	m_vehicle = { };
}

Vehicle::Vehicle(A3Vehicle vehicle)
{
	m_vehicle = vehicle;
}

bool Vehicle::Update()
{
	m_box = { };

	m_visual_state = m_vehicle.GetFutureVisualState();

	if (m_visual_state.GetOrigin().Zero())
	{
		return false;
	}

	Vector2 orig_2d = { };

	if (!g_pClient->m_camera.WorldToScreen(m_visual_state.GetOrigin(), orig_2d))
	{
		return false;
	}

	m_box = { (int)orig_2d.x, (int)orig_2d.y, 0, 0 };

	m_distance = g_pClient->m_parent.GetCurrentVisualState().GetOrigin().Distance(m_visual_state.GetOrigin());

	m_driver.Update();

	return true;
}

LocalPlayer::LocalPlayer()
{
	m_local = Address(nullptr);
}

LocalPlayer::LocalPlayer(A3Entity local)
{
	m_local = local;
}

void LocalPlayer::Update()
{
	m_visual_state = m_local.GetCurrentVisualState();

	if (m_visual_state.GetOrigin().Zero())
	{
		return;
	}

	m_health = m_local.GetHealth();

	if (m_local.IsHoldingItem())
	{
		m_active_weapon = m_local.GetActiveWeapon();
	}

	m_camera_angles = m_local.GetRealPlayer().GetCameraAngles();
}

Vector3 LocalPlayer::GetViewangles()
{
	Vector3 rotation = m_visual_state.GetRotationMatrix()[2];

	Vector3 viewAngles = {

		atan2f(rotation.x, rotation.z),

		m_camera_angles.GetViewangles().x,

		0.f
	};

	return viewAngles;
}

void LocalPlayer::SetViewangles(Vector3 viewangles)
{
	m_visual_state.SetRotation(viewangles.x);
	m_camera_angles.SetPitch(viewangles.y);
}

Vector3 LocalPlayer::GetGunPosition()
{
	Vector3 gun_model = { 0.07f, -0.0175f, 0.0f };

	Vector3 gun_world = Math::model_to_world(gun_model, m_visual_state.GetInverseRotationMatrix(), m_visual_state.GetHead());

	return gun_world;
}