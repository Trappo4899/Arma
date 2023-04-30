#include "includes.h"

Weapon::Weapon()
{
    m_address = nullptr;
    m_data = { };
}

Weapon::Weapon(Address address)
{
    m_address = address;
    m_data = { };

    if (m_address)
    {
        m_data.weapon_mode      = WeaponMode(m_address.at());
        m_data.weapon_type      = WeaponType(m_address.at(0x8));
        m_data.muzzle_type      = MuzzleType(m_address.at(0x10));
        m_data.muzzle_state     = MuzzleState(m_address.at(0x18));
    }
}

WeaponMode Weapon::GetWeaponMode()
{
    return m_data.weapon_mode;
}

WeaponType Weapon::GetWeaponType()
{
    return m_data.weapon_type;
}

MuzzleType Weapon::GetMuzzleType()
{
    return m_data.muzzle_type;
}

MuzzleState Weapon::GetMuzzleState()
{
    return m_data.muzzle_state;
}
