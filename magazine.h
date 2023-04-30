#pragma once

#include "magazine_type.h"

class MagazineType;

class Magazine
{
private:

	struct magazine_t
	{
		MagazineType magazine_type;
	};

private:

	Address m_address;
	magazine_t m_data;

public:

	Magazine();
	Magazine(Address address);

public:

	MagazineType GetMagazineType();

	void SetShootDelay();
};