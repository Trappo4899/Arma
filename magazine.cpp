#include "includes.h"

Magazine::Magazine()
{
	m_address = nullptr;
	m_data = { };
}

Magazine::Magazine(Address address)
{
	m_address = address;
	m_data = { };

	if (m_address)
	{
		m_data.magazine_type = MagazineType(m_address.at(Offsets::Magazine::MagazineType));
	}
}

MagazineType Magazine::GetMagazineType()
{
	return m_data.magazine_type;
}

void Magazine::SetShootDelay()
{
	m_address.set<float>(Offsets::Magazine::ShootDelay, 0.f);
}