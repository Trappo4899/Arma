#pragma once
#include "actionmap.h"

class MoveInfo
{
private:

	struct move_info_t
	{
		union
		{

		};
	};

private:

	Address m_address;
	move_info_t m_data;

public:

	MoveInfo();
	MoveInfo(Address address);

public:

	ActionMap GetActionMap();
};