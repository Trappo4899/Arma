#include "includes.h"

Process::Process()
{
	m_process_name = nullptr;
	m_process_id = 0;
}

Process::Process(const wchar_t* name)
{
	m_process_name = name;
	m_process_id = 0;
}

const wchar_t* Process::get_name()
{
	return m_process_name;
}

unsigned int Process::get_pid()
{
	return m_process_id;
}

Address Process::get_address()
{
	return m_address;
}

Process::operator bool()
{
	return m_process_id != 0 && m_process_name != nullptr;
}

bool Process::init(Process& process)
{
	while (!process.m_process_id)
	{
		auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (snapshot == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		PROCESSENTRY32 pe32 = { };
		pe32.dwSize = sizeof(pe32);

		if (Process32First(snapshot, &pe32))
		{
			do
			{
				if (_wcsicmp(pe32.szExeFile, process.m_process_name) == 0)
				{
					process.m_process_id = pe32.th32ProcessID;
				}
			} while (Process32Next(snapshot, &pe32));
		}

		CloseHandle(snapshot);
	}

	g_pDriver->init(process.m_process_id);

	process.m_address = g_pDriver->GetProcessBase();

	return process.m_address.as<bool>();
}