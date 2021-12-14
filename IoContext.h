#pragma once
#include <WinSock2.h>

class IoContext
{
public:
	IoContext();
	~IoContext();

	bool Initialize();

private:
	HANDLE mCompletionPort = nullptr;
};