#include "pch.h"
#include "Acceptor.h"

#include <mswsock.h>

#include "IocpOperation.h"
#include "ServerService.h"
#include "Session.h"

Acceptor::Acceptor(IoContext& ioContext, const EndPoint& endPoint, const ServerService* service)
	: mIoContext(ioContext),
	  mListenSocket(WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED)),
	  mEndPoint(endPoint),
	  mServerService(service)
{
	constexpr int optVal = TRUE;
	constexpr int optLen = sizeof(int);

	if (SOCKET_ERROR == ::setsockopt(mListenSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&optVal), optLen))
	{
		throw std::runtime_error("setsockopt error");
	}

	if (SOCKET_ERROR == ::bind(mListenSocket, reinterpret_cast<SOCKADDR*>(&mEndPoint.GetSockAddr()), sizeof(SOCKADDR_IN)))
	{
		throw std::runtime_error("bind error");
	}

	if (SOCKET_ERROR == ::listen(mListenSocket, SOMAXCONN))
	{
		throw std::runtime_error("listen error");
	}

	if (false == ioContext.RegisterIocpHandle(reinterpret_cast<HANDLE>(mListenSocket)))
	{
		throw std::runtime_error("register error");
	}
}

void Acceptor::Accept()
{
	auto session = mServerService->GetSession();

	if (nullptr == mAcceptOperation)
	{
		mAcceptOperation = std::make_shared<IocpOperation>(IoType::Accept,
			[this](IocpOperation* operation, const std::size_t bytesTransferred)
			{
				const auto session = operation->GetSession();

				if (::setsockopt(session->GetSocket(), SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, reinterpret_cast<char*>(&mListenSocket), sizeof(SOCKET)) == SOCKET_ERROR)
				{
					const int error = ::WSAGetLastError();
					spdlog::error("Accept setsockeopt error: {}", error);
					Accept();
					return;
				}

				SOCKADDR_IN sockAddress{};
				int size = sizeof(sockAddress);
				if (SOCKET_ERROR == ::getpeername(session->GetSocket(), reinterpret_cast<SOCKADDR*>(&sockAddress), &size))
				{
					const int error = ::WSAGetLastError();
					spdlog::error("Accept setsockeopt error: {}", error);
					Accept();
					return;
				}

				spdlog::info("Session connected.");

				session->SetEndPoint(EndPoint{ sockAddress });
				session->SetConnected();
				session->BeginReceive();

			}, session.get());
	}	

	DWORD bytesTransferred = 0;

	if (false == ::AcceptEx(mListenSocket, session->GetSocket(), session->mRecvBuffer.WritePos(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &bytesTransferred, mAcceptOperation.get()))
	{
		const int error = ::WSAGetLastError();
		if (error != WSA_IO_PENDING)
		{
			spdlog::error("AcceptEx error: {}", error);
			Accept();
		}
	}
}
