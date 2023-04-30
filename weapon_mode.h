#pragma once

class WeaponMode
{
private:

	struct weapon_mode_t
	{
		std::string firerate;
	};

private:

	Address m_address;
	weapon_mode_t m_data;

public:

	WeaponMode();
	WeaponMode(Address address);

public:

	std::string GetFirerate();
};