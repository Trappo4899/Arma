#ifndef PROCESS_H
#define PROCESS_H

#include "address.h"

class Process
{
private:

	const wchar_t* m_process_name;
	unsigned int m_process_id;
	Address m_address;

public:

	Process();
	Process(const wchar_t* name);

	const wchar_t* get_name();
	unsigned int get_pid();
	Address get_address();

	operator bool();

	static bool init(Process& process);
};

#endif