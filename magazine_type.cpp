#include "includes.h"

MagazineType::MagazineType()
{
	m_address = nullptr;
	m_data = { };
}

MagazineType::MagazineType(Address address)
{
	m_address = address;
	m_data = { };

	if (m_address)
	{
		m_data = m_address.at<magazine_type_t>();

		ammo_type = AmmoType(m_address.at(Offsets::MagazineType::AmmoType));
	}
}

AmmoType MagazineType::GetAmmoType()
{
	return ammo_type;
}

FLOAT MagazineType::GetMaxLeadSpeed()
{
	return m_data.max_lead_speed;
}

FLOAT MagazineType::GetInitialSpeed()
{
	return m_data.initial_speed;
}

FLOAT MagazineType::GetMaxThrowHoldTime()
{
	return m_data.max_throw_hold_time;
}

FLOAT MagazineType::GetMinThrowIntensityCoef()
{
	return m_data.min_throw_intensity_coef;
}

FLOAT MagazineType::GetMaxThrowIntensityCoef()
{
	return m_data.max_throw_intensity_coef;
}