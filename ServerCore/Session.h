#pragma once
#include "EndPoint.h"
#include "RecvBuffer.h"
#include <memory>

class ServerService;
class IocpOperation;
class IoContext;
class SendBuffer;

class Session : public std::enable_shared_from_this<Session>
{
	constexpr static int BufferSize = 65536;
public:
	explicit Session(const IoContext& ioContext, ServerService& serverService);
	virtual ~Session()
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
	virtual void OnDisconnected() = 0;
	virtual void OnConnected() = 0;
	virtual int OnRecv(std::byte* recvBuffer, const int len) = 0;

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

	ServerService& _serverService;
};

struct PacketHeader
{
	uint16 mSize = 0;
	uint16 mId = 0;
};

class PacketSession : public Session
{
public:
	explicit PacketSession(const IoContext& ioContext, ServerService& serverService)
		: Session(ioContext, serverService)
	{		
	}

	~PacketSession() override = default;

	int OnRecv(std::byte* recvBuffer, const int len) override
	{
		int processLength = 0;

		while (true)
		{
			const int dataSize = len - processLength;

			if (dataSize < sizeof PacketHeader)
			{
				break;
			}

			const auto [size, id] = *reinterpret_cast<const PacketHeader*>(&recvBuffer[processLength]);

			if (dataSize < size)
			{
				break;
			}

			OnRecvPacket(&recvBuffer[processLength], size);

			processLength += size;
		}

		return processLength;
	}

	virtual void OnRecvPacket(std::byte* recvBuffer, const int len) abstract;
};