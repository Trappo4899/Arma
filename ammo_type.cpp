#include "includes.h"

AmmoType::AmmoType()
{
	m_address = nullptr;
	m_data = { };
	m_once = false;
	m_old_caliber = 0.f;
}

AmmoType::AmmoType(Address address)
{
	m_address = address;
	
	if (m_address)
	{
		m_data = m_address.at<ammo_type_t>();
	}

	m_once = false;
	m_old_caliber = 0.f;
}

float AmmoType::GetCaliber()
{
	return m_data.caliber;
}

void AmmoType::SetCaliber(float caliber)
{
	if (!m_once)
	{
		m_old_caliber = this->GetCaliber();
		m_once = true;
	}
	
	m_address.set<float>(Offsets::AmmoType::Caliber, caliber);
}

void AmmoType::ResetCaliber()
{
	m_address.set<float>(Offsets::AmmoType::Caliber, m_old_caliber);

	m_once = false;
}

float AmmoType::GetMaxControlRange()
{
	return m_data.max_control_range;
}

float AmmoType::GetThrustTime()
{
	return m_data.thrust_time;
}

float AmmoType::GetThrust()
{
	return m_data.thrust;
}

float AmmoType::GetTimeToLive()
{
	return m_data.time_to_live;
}

float AmmoType::GetAirFriction()
{
	return m_data.air_friction;
}

float AmmoType::GetWaterFriction()
{
	return m_data.water_friction;
}

float AmmoType::GetGravityCoef()
{
	return m_data.gravity_coef;
}

float AmmoType::GetTypicalSpeed()
{
	return m_data.typical_speed;
}