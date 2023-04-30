#pragma once
#include "moveinfo.h"

class MovesType
{
private:

	struct moves_type_t
	{
		union
		{

		};
	};

private:

	Address m_address;
	moves_type_t m_data;

public:

	MovesType();
	MovesType(Address address);

public:

	MoveInfo GetMoveInfo(int idx);

};