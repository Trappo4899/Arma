#include "includes.h"

DX11Engine::DX11Engine()
{
	m_address = nullptr;
	m_data = { };
}

DX11Engine::DX11Engine(Address address)
{
	m_address = address;
	m_data = m_address.at<dx11_engine_t>();
}

void DX11Engine::Update()
{
	m_data = m_address.at<dx11_engine_t>();
}

Address DX11Engine::GetAddress()
{
	return m_address;
}

void DX11Engine::SetFov(float width, float height, float Fov)
{
	float rad_fov = Math::deg_to_rad(Fov);

	float calculated_fov = ((atanf(rad_fov / 2.f) * (width / height)) * 2.f);

	float deg_fov = Math::rad_to_deg(calculated_fov);

	deg_fov = ceil(deg_fov);

	float fovTop = (deg_fov * 0.01194f);
	float fovLeft = ((fovTop / width) * height);

	m_address.set(Offsets::DX11Engine::FovTop, fovTop);
	m_address.set(Offsets::DX11Engine::FovLeft, fovLeft);
}

float DX11Engine::GetFov()
{
	float fovTop = m_data.FovTop;
	float fovLeft = m_data.FovLeft;

	float calculated_fov = atanf(m_data.FovTop / (2.f * m_data.ScreenHeight / tanf(Math::deg_to_rad(m_data.FovLeft / 2.f)))) * 2.f;

	return Math::rad_to_deg(calculated_fov);
}

INT32 DX11Engine::GetScreenWidth()
{
	return m_data.ScreenWidth;
}

INT32 DX11Engine::GetScreenHeight()
{
	return m_data.ScreenHeight;
}

void DX11Engine::Handle()
{
	if (g_pMiscSettings->m_zoom->IsActive())
	{
		this->SetFov(g_pMiscSettings->m_width->get(), g_pMiscSettings->m_height->get(), g_pMiscSettings->m_zoom_amount->get());
	}
	else
	{
		this->SetFov(g_pMiscSettings->m_width->get(), g_pMiscSettings->m_height->get(), g_pMiscSettings->m_fov->get());
	}
}
