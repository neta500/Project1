#include "pch.h"
#include "Session.h"

#include "IoContext.h"
#include "IocpOperation.h"
#include "SocketUtils.h"
#include "SendBuffer.h"

Session::Session(const IoContext& ioContext)
	: mSocket(WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED)), mEndPoint()
{
	spdlog::info("Session constructor");

	// TODO : 소켓세팅 공통함수로 빼기 (Socket 클래스 제작, SocketUtils.h 참고)
	constexpr int optVal = TRUE;
	constexpr int optLen = sizeof(int);

	if (SOCKET_ERROR == ::setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&optVal), optLen))
	{
		throw std::runtime_error("setsockopt error");
	}

	ioContext.RegisterIocpHandle(reinterpret_cast<HANDLE>(mSocket));
		
	// TODO : 순환참조 제거, callback 함수 따로 정의. 람다 파라미터에 IocpOperation*이 꼭필요한가?
	mRecvOperation = std::make_shared<IocpOperation>(IoType::Recv,
		[this](IocpOperation* operation, const std::size_t byteTransferred)
		{
			if (byteTransferred == 0)
			{
				BeginDisconnect();
				return;
			}

			if (false == mRecvBuffer.OnWrite(static_cast<int>(byteTransferred)))
			{
				// log
				BeginDisconnect();
				return;
			}

			const int dataSize = mRecvBuffer.DataSize();
			const int processSize = OnRecv(mRecvBuffer.ReadPos(), dataSize);

			if (processSize < 0 || dataSize < processSize)
			{
				// log
				BeginDisconnect();
				return;
			}

			if (false == mRecvBuffer.OnRead(processSize))
			{
				// log
				BeginDisconnect();
				return;
			}			

			mRecvBuffer.Clean();

			BeginReceive();
		}, this);

	mDisconnectOperation = std::make_shared<IocpOperation>(IoType::Disconnect,
		[this](IocpOperation* operation, const std::size_t byteTransferred)
		{
			spdlog::info("Session Disconnected: {}", mSocket);
		}, this);

	mSendOperation = std::make_shared<IocpOperation>(IoType::Send,
		[this](IocpOperation* operation, const std::size_t byteTransferred)
		{
			mSendOperation->mSendBufferVec.clear();

			if (byteTransferred == 0)
			{
				BeginDisconnect();
				return;
			}

			std::scoped_lock lock(mSendQueueMutex);
			if (mSendQueue.empty())
			{
				mSendRegistered = false;
			}
			else
			{
				RegisterSend();
			}

		}, this);
}

void Session::BeginReceive()
{
	if (false == mConnected.load())
	{
		return;
	}	
	
	DWORD recvBytes = 0;
	DWORD flags = 0;

	WSABUF wsaBuf{};
	wsaBuf.buf = reinterpret_cast<char*>(mRecvBuffer.WritePos());
	wsaBuf.len = static_cast<ULONG>(mRecvBuffer.FreeSize());

	if (SOCKET_ERROR == ::WSARecv(mSocket, &wsaBuf, 1, &recvBytes, &flags, mRecvOperation.get(), nullptr))
	{
		const int error = ::WSAGetLastError();
		if (error != WSA_IO_PENDING)
		{
			spdlog::error("WSARecv error: {}", error);
		}
	}
}

void Session::BeginSend(std::shared_ptr<SendBuffer> sendBuffer)
{
	std::scoped_lock lock(mSendQueueMutex);

	mSendQueue.push(sendBuffer);
	if (mSendRegistered.exchange(true) == false)
	{
		RegisterSend();
	}
}

void Session::RegisterSend()
{
	if (false == mConnected.load())
	{
		return;
	}

	{
		std::scoped_lock lock(mSendQueueMutex);

		int writeSize = 0;
		while (mSendQueue.empty() == false)
		{
			std::shared_ptr<SendBuffer> front = mSendQueue.front();
			writeSize += front->WriteSize();
			mSendQueue.pop();
			mSendOperation->mSendBufferVec.emplace_back(front);
		}
	}

	std::vector<WSABUF> wsaBufs;
	wsaBufs.reserve(mSendOperation->mSendBufferVec.size());
	for (const std::shared_ptr<SendBuffer> sendBuffer : mSendOperation->mSendBufferVec)
	{
		WSABUF wsaBuf{};
		wsaBuf.buf = reinterpret_cast<char*>(sendBuffer->Buffer());
		wsaBuf.len = static_cast<ULONG>(sendBuffer->WriteSize());
		wsaBufs.emplace_back(wsaBuf);
	}

	DWORD sendBytes = 0;

	if (SOCKET_ERROR == ::WSASend(mSocket, wsaBufs.data(), static_cast<DWORD>(wsaBufs.size()), &sendBytes, 0, mSendOperation.get(), nullptr))
	{
		const int error = ::WSAGetLastError();
		if (error != WSA_IO_PENDING)
		{
			spdlog::error("WSASend error: {}", error);

			mSendOperation->mSendBufferVec.clear();
			mSendRegistered = false;
		}
	}
}

void Session::BeginConnect()
{
}

void Session::BeginDisconnect()
{
	if (false == mConnected.exchange(false))
	{
		return;
	}

	if (false == ::DisconnectEx(mSocket, mDisconnectOperation.get(), TF_REUSE_SOCKET, 0))
	{
		const int error = ::WSAGetLastError();
		if (WSA_IO_PENDING != error)
		{
			spdlog::error("DisconnectEx error: {}", error);
		}
	}
}
