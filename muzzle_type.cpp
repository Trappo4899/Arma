#include "includes.h"

MuzzleType::MuzzleType()
{
	m_address = nullptr;
	m_data = { };
}

MuzzleType::MuzzleType(Address address)
{
	m_address = address;
	m_data = { };
}