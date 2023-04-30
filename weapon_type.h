#pragma once

class WeaponType
{
private:

	std::string name;
	std::string type;
	std::string family;

	struct weapon_type_t
	{
		union
		{
			DEFINE_MEMBER_N(FLOAT, scope_in_speed, 0x4EC);
			DEFINE_MEMBER_N(FLOAT, inertia, 0x4F0);
			DEFINE_MEMBER_N(FLOAT, initial_speed, 0x4F4);
		};
	};

private:

	Address m_address;
	weapon_type_t m_data;

public:

	WeaponType();
	WeaponType(Address address);

public:

	std::string GetName();
	std::string GetType();
	std::string GetFamily();

	float GetScopeInSpeed();
	void SetScopeInSpeed(float speed);

	float GetInertia();
	void SetInertia(float inertia);

	float GetInitialSpeed();
};