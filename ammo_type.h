#pragma once

class AmmoType
{
private:

	bool m_once;
	float m_old_caliber;

	struct ammo_type_t
	{
		union
		{
			DEFINE_MEMBER_N(FLOAT, max_control_range, 0x398);
			DEFINE_MEMBER_N(FLOAT, thrust_time, 0x3C4);
			DEFINE_MEMBER_N(FLOAT, thrust, 0x3C8);
			DEFINE_MEMBER_N(FLOAT, caliber, 0x404);
			DEFINE_MEMBER_N(FLOAT, time_to_live, 0x410);
			DEFINE_MEMBER_N(FLOAT, air_friction, 0x418);
			DEFINE_MEMBER_N(FLOAT, water_friction, 0x41C);
			DEFINE_MEMBER_N(FLOAT, gravity_coef, 0x420);
			DEFINE_MEMBER_N(FLOAT, typical_speed, 0x424);
		};
	};

private:

	Address m_address;
	ammo_type_t m_data;

public:

	AmmoType();
	AmmoType(Address address);

public:

	float GetCaliber();
	void SetCaliber(float caliber);
	void ResetCaliber();

	float GetMaxControlRange();
	float GetThrustTime();
	float GetThrust();
	float GetTimeToLive();
	float GetAirFriction();
	float GetWaterFriction();
	float GetGravityCoef();
	float GetTypicalSpeed();
};