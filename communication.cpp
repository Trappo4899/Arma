#include "includes.h"

Driver::Driver()
{
	LoadLibraryA("user32.dll");

	NtCompositionThread = reinterpret_cast<tNtCompositionInputThread*>(GetProcAddress(LoadLibraryA("win32u.dll"), "NtCompositionInputThread"));
}

Driver::Driver(UINT64 PID) : PID{ PID }
{
	LoadLibraryA("user32.dll");

	NtCompositionThread = reinterpret_cast<tNtCompositionInputThread*>(GetProcAddress(LoadLibraryA("win32u.dll"), "NtCompositionInputThread"));
}

void Driver::init(UINT64 ProcessID)
{
	this->PID = ProcessID;
}

bool Driver::IsLoaded()
{
	Comms::Request loadedRequest = { };

	loadedRequest.type = Comms::Type::IsLoaded;
	loadedRequest.Key = Comms::Key;
	loadedRequest.Return = Comms::Failure;

	NtCompositionThread((long long)&loadedRequest, 0, 0);

	return loadedRequest.Return == Comms::Success;
}

bool Driver::ReadMemory(PVOID Address, PVOID Buffer, SIZE_T Size)
{
	static auto sourcepid = _getpid();

	Comms::Request ReadMemoryRequest = { };

	ReadMemoryRequest.type = Comms::Type::ReadMemory;
	ReadMemoryRequest.Key = Comms::Key;
	ReadMemoryRequest.Return = Comms::Failure;

	ReadMemoryRequest.PID = this->PID;
	ReadMemoryRequest.SrcPID = sourcepid;

	ReadMemoryRequest.Address = Address;
	ReadMemoryRequest.Buffer = Buffer;
	ReadMemoryRequest.Size = Size;

	NtCompositionThread((long long)&ReadMemoryRequest, 0, 0);

	return ReadMemoryRequest.Return == Comms::Success;
}

bool Driver::WriteMemory(PVOID Address, PVOID NewValue, SIZE_T Size)
{
	static auto sourcepid = _getpid();

	Comms::Request WriteMemoryRequest = { };

	WriteMemoryRequest.type = Comms::Type::WriteMemory;
	WriteMemoryRequest.Key = Comms::Key;
	WriteMemoryRequest.Return = Comms::Failure;

	WriteMemoryRequest.PID = this->PID;
	WriteMemoryRequest.SrcPID = sourcepid;

	WriteMemoryRequest.Address = Address;
	WriteMemoryRequest.Buffer = NewValue;
	WriteMemoryRequest.Size = Size;

	NtCompositionThread((long long)&WriteMemoryRequest, 0, 0);

	return WriteMemoryRequest.Return == Comms::Success;
}

UINT64 Driver::GetProcessBase()
{
	Comms::Request GetProcessBaseRequest = { };

	GetProcessBaseRequest.type = Comms::Type::GetProcessBase;
	GetProcessBaseRequest.Key = Comms::Key;
	GetProcessBaseRequest.Return = Comms::Failure;

	GetProcessBaseRequest.PID = this->PID;

	NtCompositionThread((long long)&GetProcessBaseRequest, 0, 0);

	return GetProcessBaseRequest.Return;
}