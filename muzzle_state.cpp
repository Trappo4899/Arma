#include "includes.h"

MuzzleState::MuzzleState()
{
	m_address = nullptr;
	m_data = { };
}

MuzzleState::MuzzleState(Address address)
{
	m_address = address;
	m_data = { };

	if (m_address)
	{
		m_data.magazine = Magazine(m_address.at(Offsets::MuzzleState::Magazine));
	}
}

Magazine MuzzleState::GetMagazine()
{
	return m_data.magazine;
}