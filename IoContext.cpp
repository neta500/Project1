#include "IoContext.h"

#include "spdlog/spdlog.h"

bool IoContext::Initialize()
{
	WSADATA wsaData{};
	if (false == WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		spdlog::error("WSAStartup failed : {}", WSAGetLastError());
		return false;
	}

	mCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
	if (mCompletionPort == INVALID_HANDLE_VALUE)
	{
		spdlog::error("CreateIoCompletionPort failed : {}", WSAGetLastError());
		return false;
	}

	return true;
}

