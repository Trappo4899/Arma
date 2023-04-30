#include "includes.h"

EntityType::EntityType()
{
	m_address = nullptr;
	m_data = { };
}

EntityType::EntityType(Address address)
{
	m_address = address;
	m_data = { };

	if (m_address)
	{
		m_data.name			= g_pDriver->ReadString(m_address.at<UINT64>(Offsets::EntityType::Name));
		m_data.path			= g_pDriver->ReadString(m_address.at<UINT64>(Offsets::EntityType::Path));
		m_data.className	= g_pDriver->ReadString(m_address.at<UINT64>(Offsets::EntityType::Class));
		m_data.print		= g_pDriver->ReadString(m_address.at<UINT64>(Offsets::EntityType::Print));
		m_data.type			= g_pDriver->ReadString(m_address.at<UINT64>(Offsets::EntityType::Type));
	}
}

std::string EntityType::GetName()
{
	return m_data.name;
}

std::string EntityType::GetPath()
{
	return m_data.path;
}

std::string EntityType::GetClass()
{
	return m_data.className;
}

std::string EntityType::GetPrint()
{
	return m_data.print;
}

std::string EntityType::GetType()
{
	return m_data.type;
}

MovesType EntityType::GetMovesType()
{
	return m_address.at(Offsets::EntityType::MovesType);
}

bool EntityType::IsPlayer()
{
	return _stricmp(XOR("soldier"), m_data.className.c_str()) == 0;
}

bool EntityType::IsVehicle()
{
	return	_stricmp(XOR("carx"), m_data.className.c_str())				== 0 ||
			_stricmp(XOR("tankx"), m_data.className.c_str())			== 0 ||
			_stricmp(XOR("helicopterrtd"), m_data.className.c_str())	== 0 ||
			_stricmp(XOR("shipx"), m_data.className.c_str())			== 0 ||
			_stricmp(XOR("paraglide"), m_data.className.c_str())		== 0;
}

bool EntityType::IsWildlife()
{
	return _stricmp(XOR("animal"), m_data.className.c_str()) == 0;
}
