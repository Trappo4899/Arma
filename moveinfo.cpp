#include "includes.h"

MoveInfo::MoveInfo()
{
	m_address = nullptr;
	m_data = { };
}

MoveInfo::MoveInfo(Address address)
{
	m_address = address;
	m_data = m_address.at<move_info_t>();
}

ActionMap MoveInfo::GetActionMap()
{
	return ActionMap(m_address.at(Offsets::MoveInfo::ActionMap));
}