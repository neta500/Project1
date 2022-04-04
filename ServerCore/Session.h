#pragma once
#include "EndPoint.h"

class IocpOperation;
class IoContext;

class Session
{
public:
	Session(const IoContext& ioContext);
	~Session()
	{
		spdlog::info("Session destructor : {}", static_cast<int>(mSocket));
	}

	void Receive();
	void Send(const std::string& str);

	void Connect();
	void Disconnect();
	
	bool IsConnected() const { return mConnected; }
	SOCKET GetSocket() const { return mSocket; }

	void SetConnected() { mConnected = true; }
	void SetEndPoint(const EndPoint& endPoint) { mEndPoint = endPoint; }

public:
	std::array<char, 256> mRecvBuffer{};

private:
	SOCKET mSocket;
	EndPoint mEndPoint;

	std::atomic<bool> mConnected = false;
	std::shared_ptr<IocpOperation> mRecvOperation = nullptr;
};
