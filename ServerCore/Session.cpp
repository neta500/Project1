#include "pch.h"
#include "Session.h"

#include "IoContext.h"
#include "IocpOperation.h"

Session::Session(const IoContext& ioContext)
	: mSocket(WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED)), mEndPoint()
{
	spdlog::info("Session constructor");

	// TODO : 소켓세팅 공통함수로 빼기
	constexpr int optVal = TRUE;
	constexpr int optLen = sizeof(int);

	if (SOCKET_ERROR == ::setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&optVal), optLen))
	{
		throw std::runtime_error("setsockopt error");
	}

	ioContext.RegisterIocpHandle(reinterpret_cast<HANDLE>(mSocket));
		
	// TODO : 순환참조 제거
	mRecvOperation = std::make_shared<IocpOperation>(IoType::Recv,
		[this](IocpOperation* operation, const std::size_t byteTransferred)
		{
			if (byteTransferred == 0)
			{
				Disconnect();
				return;
			}

			spdlog::info("Recv: {} - {}", byteTransferred, mRecvBuffer.data());

			Receive();
		}, std::shared_ptr<Session>(this));
}

void Session::Receive()
{
	if (false == mConnected)
	{
		return;
	}	
	
	DWORD bytesTransferred = 0;
	DWORD flags = 0;

	WSABUF wsaBuf{};
	wsaBuf.buf = mRecvBuffer.data();
	wsaBuf.len = static_cast<ULONG>(mRecvBuffer.size());

	if (SOCKET_ERROR == ::WSARecv(mSocket, &wsaBuf, 1, &bytesTransferred, &flags, mRecvOperation.get(), nullptr))
	{
		const int error = ::WSAGetLastError();
		if (error != WSA_IO_PENDING)
		{
			spdlog::error("WSARecv error: {}", error);
		}
	}
}

void Session::Disconnect()
{
}
