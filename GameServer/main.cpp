#include "pch.h"
#include <iostream>
#include <SpinLock.h>
#include <ThreadManager.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	spdlog::info("init spdlog");

	WSAData wsaData{};
	if (::WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		return 0;
	}

	// listenSocket
	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		const auto errCode = ::WSAGetLastError();
		spdlog::error("socket error: {}", errCode);
		return 0;
	}

	// addr
	SOCKADDR_IN serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(712);

	// bind
	if (SOCKET_ERROR == ::bind(listenSocket, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)))
	{
		const auto errCode = ::WSAGetLastError();
		spdlog::error("socket error: {}", errCode);
		return 0;
	}

	// listen
	if (SOCKET_ERROR == ::listen(listenSocket, 10))
	{
		const auto errCode = ::WSAGetLastError();
		spdlog::error("socket error: {}", errCode);
		return 0;		
	}

	SOCKADDR_IN clientAddr{};
	int size = sizeof(clientAddr);
	SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &size);
	if (clientSocket == INVALID_SOCKET)
	{
		const auto errCode = ::WSAGetLastError();
		spdlog::error("socket error: {}", errCode);
		return 0;
	}

	char clientIpAddr[16];
	::inet_ntop(AF_INET, &clientAddr.sin_addr, clientIpAddr, sizeof(clientIpAddr));
	spdlog::info("client connected : {}", clientIpAddr);

	// accept
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(5));

		// recv
		char recvBuffer[1000]{};

		int recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
		if (recvLen < 0)
		{
			const auto errCode = ::WSAGetLastError();
			spdlog::error("recv error: {}", errCode);
			return 0;
		}

		spdlog::info("recv: {} {}", recvBuffer, recvLen);

		// send
		std::string sendBuffer = "ECHO-" + std::string{recvBuffer};

		auto result = ::send(clientSocket, sendBuffer.c_str(), sendBuffer.size(), 0);
		if (result == SOCKET_ERROR)
		{
			const auto errCode = ::WSAGetLastError();
			spdlog::error("send error: {}", errCode);
			return 0;
		}
	}
	

	::WSACleanup();
	return 0;
}
