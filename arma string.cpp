#include "includes.h"

ArmaString::ArmaString()
{
	m_address = 0;
	m_data = { };
}

ArmaString::ArmaString(UINT_PTR address)
{
	m_address = address;
	m_data = g_pDriver->Read<A3_STRING_DATA_T>(m_address);
}

void ArmaString::Update()
{
	m_data = g_pDriver->Read<A3_STRING_DATA_T>(m_address);
}

ArmaString::A3_STRING_DATA_T ArmaString::GetData()
{
	return m_data;
}