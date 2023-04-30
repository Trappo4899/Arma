#pragma once

#include "magazine.h"

class Magazine;

class MuzzleState
{
private:

	struct muzzle_state_t
	{
		Magazine magazine;
	};

private:

	Address m_address;
	muzzle_state_t m_data;

public:

	MuzzleState();
	MuzzleState(Address address);

public:

	Magazine GetMagazine();
};