#pragma once

class EndPoint
{
public:
	EndPoint() = default;
	EndPoint(const std::string& ip, const uint16 port) : mIp(ip), mPort(port)
	{
		mSocketAddress.sin_family = AF_INET;
		// TODO : IPv4(ip) compile time value check (x.x.x.x)
		::inet_pton(AF_INET, ip.c_str(), &mSocketAddress.sin_addr);
		mSocketAddress.sin_port = ::htons(port);
	}

	explicit EndPoint(const SOCKADDR_IN& sockAddr)
		: mSocketAddress(sockAddr)
	{
		std::array<char, INET_ADDRSTRLEN> ip{};
		::inet_ntop(AF_INET, &mSocketAddress.sin_addr, ip.data(), INET_ADDRSTRLEN);
		mIp = ip.data();
		mPort = ::ntohs(mSocketAddress.sin_port);
	}

	std::string GetIp() const { return mIp;	}
	uint16 GetPort() const { return mSocketAddress.sin_port; }

	SOCKADDR_IN GetSockAddr() const { return mSocketAddress; }
	SOCKADDR_IN& GetSockAddr() { return mSocketAddress; }

private:
	std::string mIp;
	uint16 mPort = 0;

	SOCKADDR_IN mSocketAddress{};
};