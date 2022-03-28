#pragma once
#include "EndPoint.h"

class IocpOperation;

class Session : std::enable_shared_from_this<Session>
{
public:
	Session();
	~Session() = default;

	void Receive();
	void Send();

	void Connect();
	void Disconnect();
	
	bool IsConnected() const { return mConnected; }
	SOCKET GetSocket() const { return mSocket; }

	void SetEndPoint(const EndPoint& endPoint) { mEndPoint = endPoint; }

public:
	std::array<char, 256> mRecvBuffer{};

private:
	SOCKET mSocket;
	EndPoint mEndPoint;

	std::atomic<bool> mConnected = false;
};
