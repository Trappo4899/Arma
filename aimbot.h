#pragma once

class CAimbot
{
private:

	LocalPlayer m_local;
	A3Entity m_last_aim_ent;

	bool m_find_new_target;

private:

	clock_t start_time;
	float curr_time;
	float max_time;

public:

	Vector2 m_pred;

private:

	Vector3 GetHitbox(Entity entity);

	Vector3 CalculateAngle(Vector3 to, Vector3 from);
	Vector3 CalculatePosition(Entity entity);

	float GetTimeToTarget(Entity entity, Vector3 hitbox);
	float CalculateAngle(float rad);
	float step(float wDist);

	Vector3 GetDistanceTravelled(Entity entity, Vector3 hitbox, Vector3 angle, float distance);

	void handle_smoothing(Vector3& va, Entity ent, const clock_t begin);

public:

	Entity GetClosesetEntity(Vector3& angle_out);

	bool think();
};

extern std::unique_ptr<CAimbot> g_pAimbot;