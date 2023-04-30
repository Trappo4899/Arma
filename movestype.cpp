#include "includes.h"

MovesType::MovesType()
{
	m_address = nullptr;
	m_data = { };
}

MovesType::MovesType(Address address)
{
	m_address = address;
	m_data = m_address.at<moves_type_t>();
}

MoveInfo MovesType::GetMoveInfo(int idx)
{
	return MoveInfo(m_address.at(Offsets::MovesType::MoveInfoTable).at(0x8 * idx));
}