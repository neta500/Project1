#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <MSWSock.h>
#include "Overlapped.h"

class IoContext;

class EndPoint
{
public:
	EndPoint(const std::string& ip, const uint16 port)
	{
		mSocketAddress.sin_family = AF_INET;
		// TODO : IPv4(ip) compile time value check (x.x.x.x)
		::inet_pton(AF_INET, ip.c_str(), &mSocketAddress.sin_addr);		
		mSocketAddress.sin_port = port;
	}

	std::string GetIp() const
	{
		std::array<char, INET_ADDRSTRLEN> ip{};
		::inet_ntop(AF_INET, &mSocketAddress.sin_addr, ip.data(), INET_ADDRSTRLEN);
		return ip.data();
	}

	uint16 GetPort() const { return mSocketAddress.sin_port; }

	SOCKADDR_IN GetSockAddr() const { return mSocketAddress; }
	SOCKADDR_IN& GetSockAddr() { return mSocketAddress; }

private:
	SOCKADDR_IN mSocketAddress{};
};

// bind, listen, accept
class Acceptor
{
public:
	Acceptor(IoContext& ioContext, const EndPoint& endPoint)
		: mIoContext(ioContext), mEndPoint(endPoint)
	{
		constexpr int optVal = TRUE;
		constexpr int optLen = sizeof(int);

		if (SOCKET_ERROR == ::setsockopt(mListenSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&optVal), optLen))
		{
			throw std::runtime_error("setsockopt error");
		}

		if (SOCKET_ERROR == ::bind(mListenSocket, reinterpret_cast<SOCKADDR*>(&mEndPoint.GetSockAddr()), sizeof(SOCKADDR_IN)))
		{
			throw std::runtime_error("bind error");
		}

		if (SOCKET_ERROR == ::listen(mListenSocket, SOMAXCONN))
		{
			throw std::runtime_error("listen error");
		}
	}

	void Accept()
	{
		auto overlapped = std::make_shared<IocpOperation>(IoType::Accept);
	}	

private:
	IoContext& mIoContext;
	SOCKET mListenSocket = 0;
	EndPoint mEndPoint;
};


class IoContext
{
public:
	IoContext();
	~IoContext();

	bool Initialize();
	void Run();

private:
	HANDLE mIocpHandle = nullptr;
};