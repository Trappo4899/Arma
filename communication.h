#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "arma string.h"

typedef __int64 tNtCompositionInputThread(__int64 a1, __int64 a2, unsigned int a3);

namespace Comms
{
	constexpr UINT64 Success = 0x100;
	constexpr UINT64 Failure = 0x101;
	constexpr UINT64 Key = 0x111;

	enum Type
	{
		IsLoaded,
		Unload,
		GetProcessBase,
		GetModuleBase,
		ReadMemory,
		WriteMemory,
		SpoofThread,
		CleanupThread,
		HideWindow,
		SpoofWindow,
	};

	struct Request
	{
		// needed things for any request
		Type type;
		UINT64 Key;
		UINT64 Return;

		// specific for requests to do with a process
		UINT64 PID;
		LPCWSTR ModuleName;

		// thread specific requests
		UINT64 ThreadID;

		// specific for requests to do with r / w
		UINT64 SrcPID;
		PVOID Address;
		PVOID Buffer;
		SIZE_T Size;

		// Specific for requests to do with windows
		HANDLE hWnd;
		bool restoreWind;
	};
}

class Driver
{
private:

	UINT64 PID;

	tNtCompositionInputThread* NtCompositionThread = nullptr;

public:

	Driver();
	Driver(UINT64 PID);

	void init(UINT64 ProcessID);

	bool IsLoaded();
	bool ReadMemory(PVOID Address, PVOID Buffer, SIZE_T Size);
	bool WriteMemory(PVOID Address, PVOID NewValue, SIZE_T Size);

	UINT64 GetProcessBase();

	template <typename T>
	T Read(UINT64 Address)
	{
		T Return = { };

		if (ReadMemory(reinterpret_cast<PVOID>(Address), &Return, sizeof(T)))
		{
			return Return;
		}

		return Return;
	}

	template <typename T>
	bool Write(UINT64 Address, T Value)
	{
		if (WriteMemory(reinterpret_cast<PVOID>(Address), &Value, sizeof(T)))
		{
			return true;
		}

		return false;
	}

	std::string ReadString(UINT64 address)
	{
		//auto string = ArmaString(address);

		//auto string_data = string.GetData();

		//if (!string_data.m_size || string_data.m_size > 128)
		//{
		//	return "(null)";
		//}

		//auto read = new CHAR[string_data.m_size];

		//if (read == nullptr || !read)
		//{
		//	return "(null)";
		//}

		//if (!ReadMemory(PVOID(address + 0x10), read, string_data.m_size))
		//{
		//	delete[] read;
		//	return "";
		//}

		//std::string str = read;

		//delete[] read;

		const auto stringSize = Read<std::size_t>(address + 0x8);

		char buffer[128] = { };
		if (!ReadMemory(reinterpret_cast<PVOID>(address + 0x10), &buffer, sizeof(buffer)))
		{
			return "(null)";
		}

		std::string stringValue = { };

		for (int i = 0; i < sizeof(buffer); i++)
		{
			if (buffer[i] == 0 || buffer[i] == '\0')
				break;

			stringValue += buffer[i];
		}

		return stringValue;
	}
};

extern std::unique_ptr<Driver> g_pDriver;

#endif