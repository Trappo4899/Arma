#include "includes.h"

ActionMap::ActionMap()
{
	m_address = nullptr;
	m_data = { };
}

ActionMap::ActionMap(Address address)
{
	m_address = address;
	m_data = m_address.at<action_map_t>();
}

UINT32 ActionMap::GetActionID()
{
	return m_data.ActionID;
}