#pragma once

#include "weapon_mode.h"
#include "weapon_type.h"
#include "muzzle_type.h"
#include "muzzle_state.h"

class WeaponMode;
class WeaponType;
class MuzzleType;
class MuzzleState;

class Weapon
{
private:

	struct weapon_t
	{
		WeaponMode weapon_mode;
		WeaponType weapon_type;
		MuzzleType muzzle_type;
		MuzzleState muzzle_state;
	};

private:

	Address m_address;
	weapon_t m_data;

public:

	Weapon();
	Weapon(Address address);

public:

	WeaponMode GetWeaponMode();
	WeaponType GetWeaponType();
	MuzzleType GetMuzzleType();
	MuzzleState GetMuzzleState();
};