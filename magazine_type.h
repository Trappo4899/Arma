#pragma once

#include "ammo_type.h"

class AmmoType;

class MagazineType
{
private:

	AmmoType ammo_type;

	struct magazine_type_t
	{
		union
		{
			DEFINE_MEMBER_N(FLOAT, max_lead_speed, 0x80);
			DEFINE_MEMBER_N(FLOAT, initial_speed, 0x84);
			DEFINE_MEMBER_N(FLOAT, max_throw_hold_time, 0xA8);
			DEFINE_MEMBER_N(FLOAT, min_throw_intensity_coef, 0xAC);
			DEFINE_MEMBER_N(FLOAT, max_throw_intensity_coef, 0xB0);
		};
	};

private:

	Address m_address;
	magazine_type_t m_data;

public:

	MagazineType();
	MagazineType(Address address);

public:

	AmmoType GetAmmoType();

	FLOAT GetMaxLeadSpeed();
	FLOAT GetInitialSpeed();
	FLOAT GetMaxThrowHoldTime();
	FLOAT GetMinThrowIntensityCoef();
	FLOAT GetMaxThrowIntensityCoef();
};