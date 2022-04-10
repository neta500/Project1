#pragma once
#include <WinSock2.h>
#include <MSWSock.h>

// TODO : c# 참고해서 Socket 클래스 만들기

inline bool DisconnectEx(SOCKET hSocket, LPOVERLAPPED lpOverlapped, DWORD dwFlags, DWORD reserved)
{
	static LPFN_DISCONNECTEX lpfnDisconnectEx = nullptr;

	if (lpfnDisconnectEx == nullptr)
	{
		SOCKET garbageSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		GUID guid = WSAID_DISCONNECTEX;
		DWORD bytes = 0;

		if (SOCKET_ERROR == WSAIoctl(garbageSocket, SIO_GET_EXTENSION_FUNCTION_POINTER,
			&guid, sizeof(guid),
			&lpfnDisconnectEx, sizeof(lpfnDisconnectEx),
			&bytes, nullptr, nullptr))
		{
			return false;
		}

		closesocket(garbageSocket);
	}

	return lpfnDisconnectEx(hSocket, lpOverlapped, dwFlags, reserved);
}

inline bool ConnectEx(SOCKET hSocket, const struct sockaddr* name, int nameLen,
					  PVOID lpSendBuffer, DWORD dwSendDataLength,
					  LPDWORD lpdwBytesSent, LPOVERLAPPED lpOverlapped)
{
	static LPFN_CONNECTEX lpfnConnectEx = nullptr;

	if (lpfnConnectEx == nullptr)
	{
		SOCKET garbageSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		GUID guid = WSAID_CONNECTEX;
		DWORD bytes = 0;

		if (SOCKET_ERROR == WSAIoctl(garbageSocket, SIO_GET_EXTENSION_FUNCTION_POINTER,
			&guid, sizeof(guid),
			&lpfnConnectEx, sizeof(lpfnConnectEx),
			&bytes, nullptr, nullptr))
		{
			return false;
		}

		closesocket(garbageSocket);
	}

	return lpfnConnectEx(hSocket, name, nameLen, lpSendBuffer, dwSendDataLength, lpdwBytesSent, lpOverlapped);
}