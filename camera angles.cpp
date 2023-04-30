#include "includes.h"

CameraAngles::CameraAngles()
{
	m_address = nullptr;
	m_data = { };
}

CameraAngles::CameraAngles(Address address)
{
	m_address = address;
	m_data = m_address.at<camera_angles_t>();
}

void CameraAngles::Update()
{
	m_data = m_address.at<camera_angles_t>();
}

Address CameraAngles::GetAddress()
{
	return m_address;
}

Vector2 CameraAngles::GetViewangles()
{
	return m_data.Viewangles;
}

Vector2 CameraAngles::GetFreelookAngles()
{
	return m_data.FreelookAngles;
}

void CameraAngles::SetPitch(float pitch)
{
	m_address.set(Offsets::CameraAngles::ViewAngles, pitch);
}

void CameraAngles::SetViewangles(Vector2 va)
{
	m_address.set(Offsets::CameraAngles::ViewAngles, va);
}

void CameraAngles::SetFreelookAngles(Vector2 va)
{
	m_address.set(Offsets::CameraAngles::FreeLook, va);
}