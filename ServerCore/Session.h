#pragma once
#include "EndPoint.h"
#include "RecvBuffer.h"

class IocpOperation;
class IoContext;

class Session
{
	constexpr static int BufferSize = 65536;
public:
	explicit Session(const IoContext& ioContext);
	~Session()
	{
		spdlog::info("Session destructor : {}", static_cast<int>(mSocket));
	}

	void BeginReceive();
	void BeginSend(const std::string& str);

	void Connect();
	void Disconnect();
	
	bool IsConnected() const { return mConnected; }
	SOCKET GetSocket() const { return mSocket; }

	void SetConnected() { mConnected = true; }
	void SetEndPoint(const EndPoint& endPoint) { mEndPoint = endPoint; }

protected:
	virtual int OnRecv(const std::byte* recvBuffer, const int len) { return len; }

public:
	RecvBuffer mRecvBuffer{ BufferSize };

private:
	SOCKET mSocket;
	EndPoint mEndPoint;

	std::atomic<bool> mConnected = false;
	std::shared_ptr<IocpOperation> mRecvOperation = nullptr;

};
