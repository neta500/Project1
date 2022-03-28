#include "pch.h"
#include "Session.h"
#include "IocpOperation.h"

Session::Session()
	: mSocket(WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED)), mEndPoint()
{}

void Session::Receive()
{
	if (false == mConnected)
	{
		return;
	}
	
	auto overlapped = std::make_shared<IocpOperation>(IoType::Recv,
		[this](IocpOperation* operation, const std::size_t byteTransferred)
	{
		if (byteTransferred == 0)
		{
			Disconnect();
			return;
		}

		spdlog::info("Recv: {}", mRecvBuffer.data());

		Receive();
	}, std::shared_ptr<Session>(this));

	constexpr int dwBufferCount = 1;
	DWORD bytesTransferred = 0;
	DWORD flags = 0;

	WSABUF wsaBuf{};
	wsaBuf.buf = mRecvBuffer.data();
	wsaBuf.len = static_cast<ULONG>(mRecvBuffer.size());

	if (SOCKET_ERROR == ::WSARecv(mSocket, &wsaBuf, dwBufferCount, &bytesTransferred, &flags, overlapped.get(), nullptr))
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
