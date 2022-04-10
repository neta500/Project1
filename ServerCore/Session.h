#pragma once
#include "EndPoint.h"
#include "RecvBuffer.h"

class IocpOperation;
class IoContext;
class SendBuffer;

class Session
{
	constexpr static int BufferSize = 65536;
public:
	explicit Session(const IoContext& ioContext);
	~Session()
	{
		spdlog::info("Session destructor : {}", static_cast<int>(mSocket));
		if (mSocket != INVALID_SOCKET)
		{
			::closesocket(mSocket);
			mSocket = INVALID_SOCKET;
		}
	}

	void BeginReceive();
	void BeginSend(std::shared_ptr<SendBuffer> sendBuffer);
	void RegisterSend();

	void BeginConnect();
	void BeginDisconnect();
	
	bool IsConnected() const { return mConnected; }
	SOCKET GetSocket() const { return mSocket; }

	void SetConnected() { mConnected = true; }
	void SetEndPoint(const EndPoint& endPoint) { mEndPoint = endPoint; }

protected:
	virtual int OnRecv(const std::byte* recvBuffer, const int len) { return len; }

public:
	RecvBuffer mRecvBuffer{ BufferSize };

	std::recursive_mutex mSendQueueMutex;
	std::atomic<bool> mSendRegistered = false;
	std::queue<std::shared_ptr<SendBuffer>> mSendQueue;

private:
	SOCKET mSocket;
	EndPoint mEndPoint;

	std::atomic<bool> mConnected = false;

	std::shared_ptr<IocpOperation> mSendOperation = nullptr;
	std::shared_ptr<IocpOperation> mRecvOperation = nullptr;
	std::shared_ptr<IocpOperation> mDisconnectOperation = nullptr;
};
