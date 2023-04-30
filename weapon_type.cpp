#include "includes.h"
#include "weapon_type.h"

WeaponType::WeaponType()
{
	m_address = nullptr;
	m_data = { };
}

WeaponType::WeaponType(Address address)
{
	m_address = address;
	m_data = { };

	if (m_address)
	{
		m_data = m_address.at<weapon_type_t>();

		name		= g_pDriver->ReadString(m_address.at<UINT64>(Offsets::WeaponType::Name));
		type		= g_pDriver->ReadString(m_address.at<UINT64>(Offsets::WeaponType::Type));
		family		= g_pDriver->ReadString(m_address.at<UINT64>(Offsets::WeaponType::Family));
	}
}

std::string WeaponType::GetName()
{
	return name.substr(0, name.find(" ", 8));
}

std::string WeaponType::GetType()
{
	return type;
}

std::string WeaponType::GetFamily()
{
	return family;
}

float WeaponType::GetScopeInSpeed()
{
	return m_data.scope_in_speed;
}

void WeaponType::SetScopeInSpeed(float speed)
{
	m_address.set<float>(Offsets::WeaponType::ScopeInSpeed, speed);
}

float WeaponType::GetInertia()
{
	return m_data.inertia;
}

void WeaponType::SetInertia(float inertia)
{
	m_address.set<float>(Offsets::WeaponType::Inertia, inertia);
}

float WeaponType::GetInitialSpeed()
{
	return m_data.initial_speed;
}