#include "includes.h"

Address::Address()
{
	m_address = { };
}

Address::Address(UINT_PTR addr)
{
	m_address = addr;
}

Address::Address(PVOID addr)
{
	m_address = reinterpret_cast<UINT_PTR>(addr);
}

void Address::print(const char* name)
{
	printf("[%s] 0x%llX\n", name, m_address);
}