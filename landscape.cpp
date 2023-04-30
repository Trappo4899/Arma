#include "includes.h"

Landscape::Landscape()
{
    m_address = nullptr;
    m_data = { };
}

Landscape::Landscape(Address address)
{
    m_address = address;
    m_data = m_address.at<landscape_t>();
}

void Landscape::Update()
{
    m_data = m_address.at<landscape_t>();
}

Address Landscape::GetAddress()
{
    return m_address;
}
