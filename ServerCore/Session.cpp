#include "pch.h"
#include "Session.h"

#include "IoContext.h"
#include "IocpOperation.h"
#include "SocketUtils.h"

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
		
	// TODO : 순환참조 제거, callback 함수 따로 정의
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

			// echo test
			const std::string str = mRecvBuffer.GetRecvString(byteTransferred);
			spdlog::info("Recv {} - {}", byteTransferred, str);
			BeginSend(str);

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

void Session::BeginSend(const std::string& str)
{
	if (false == mConnected.load())
	{
		return;
	}

	// TODO : 람다 IocpOperation을 shared_ptr로 바꿔서 생명유지?
	auto operation = new IocpOperation(IoType::Send,
		[this](IocpOperation* operation, const std::size_t byteTransferred)
		{
			if (byteTransferred == 0)
			{
				BeginDisconnect();
				return;				
			}

			delete operation;
			
		}, this);

	std::ranges::copy(str, std::back_inserter(operation->mSendBuffer));
	
	DWORD sendBytes = 0;
	WSABUF wsaBuf{};
	wsaBuf.buf = operation->mSendBuffer.data();
	wsaBuf.len = static_cast<ULONG>(operation->mSendBuffer.size());
	
	if (SOCKET_ERROR == ::WSASend(mSocket, &wsaBuf, 1, &sendBytes, 0, operation, nullptr))
	{
		const int error = ::WSAGetLastError();
		if (error != WSA_IO_PENDING)
		{
			spdlog::error("WSASend error: {}", error);
			delete operation;
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
