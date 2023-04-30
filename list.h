#ifndef LIST_H
#define LIST_H

#include "base class.h"

class List : public BaseClass
{
private:

	std::vector<Address> m_objects;

	Address m_list;
	UINT32 m_size;

public:

	List()
	{
		m_objects = { };
		m_list = nullptr;
		m_size = 0;
	}

	List(Address addr, UINT32 size) : m_list{ addr }, m_size{ size }
	{
		if (!m_size || m_size > 300 || !m_list.as<bool>())
		{
			return;
		}

		m_objects.resize(m_size);

		if (!g_pDriver->ReadMemory(m_list.as<PVOID>(), m_objects.data(), (m_size * 8)))
		{
			return;
		}
	}

	std::vector<Address> get_list()
	{
		return m_objects;
	}
};

#endif