#ifndef ADDRESS_H
#define ADDRESS_H

#include "communication.h"

class Address
{
	/* to do
	
	add functionality in the driver to check page permissions of memory 
	and use that to make a valid check so that we cannot accidently
	try to read invalid memory
	
	*/

private:

	UINT_PTR m_address;

public:

	Address();
	Address(UINT_PTR addr);
	Address(PVOID addr);

	void print(const char* name);

	template<typename T = Address>
	T as()
	{
		return m_address ? T(m_address) : T{ };
	}

	template<typename T = Address>
	T as(UINT_PTR offset)
	{
		return m_address ? T(m_address + offset) : T{ };
	}

	template<typename T = Address>
	T at()
	{
		return m_address ? g_pDriver->Read<T>(m_address) : T{ };
	}

	template<typename T = Address>
	T at(UINT_PTR offset)
	{
		return m_address ? g_pDriver->Read<T>(m_address + offset) : T{ };
	}

	template<typename V>
	void set(V val)
	{
		g_pDriver->Write<V>(m_address, val);
	}

	template<typename V>
	void set(UINT_PTR offset, V val)
	{
		g_pDriver->Write<V>(m_address + offset, val);
	}

	UINT_PTR operator+(Address z)
	{
		return m_address + z.m_address;
	}

	UINT_PTR operator+(UINT_PTR z)
	{
		return m_address + z;
	}

	UINT_PTR operator+(PVOID z)
	{
		return m_address + (UINT_PTR)z;
	}

	operator bool()
	{
		return m_address != 0;
	}
};

#endif