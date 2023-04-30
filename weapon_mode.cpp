#include "includes.h"

WeaponMode::WeaponMode()
{
    m_address = nullptr;
    m_data = { };
}

WeaponMode::WeaponMode(Address address)
{
    m_address = address;
    m_data = { };

    if (m_address)
    {
        m_data.firerate = g_pDriver->ReadString(m_address.at<UINT_PTR>(Offsets::WeaponMode::Firerate));
    }
}

std::string WeaponMode::GetFirerate()
{
    return std::string();
}
