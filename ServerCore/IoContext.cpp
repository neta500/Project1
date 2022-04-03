#include "pch.h"
#include "IoContext.h"

#include "IocpOperation.h"
#include "spdlog/spdlog.h"

IoContext::IoContext()
{
	WSADATA wsaData{};
	if (0 != ::WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		const int error = ::WSAGetLastError();
		spdlog::error("WSAStartup failed : {}", error);
		throw std::runtime_error("WSAStartup failed");
	}

	mIocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
	if (mIocpHandle == INVALID_HANDLE_VALUE)
	{
		spdlog::error("CreateIoCompletionPort failed : {}", ::WSAGetLastError());
		throw std::runtime_error("CreateIoCompletionport failed");
	}
}

void IoContext::Run()
{
	DWORD bytesTransferred = 0;
	DWORD_PTR completionKey = 0;
	LPOVERLAPPED overlapped = nullptr;

	if (::GetQueuedCompletionStatus(mIocpHandle, &bytesTransferred, &completionKey, &overlapped, INFINITE))
	{
		if (const auto operation = static_cast<IocpOperation*>(overlapped))
		{
			operation->Complete(bytesTransferred);
		}
	}
	else
	{
		int error = ::WSAGetLastError();
		spdlog::error("iocp error : {}", error);
	}
}

bool IoContext::RegisterIocpHandle(const HANDLE handle) const
{
	return ::CreateIoCompletionPort(handle, mIocpHandle, 0, 0);
}

void IoContext::TestPushJob()
{
	auto operation = new IocpOperation(IoType::Recv, [](IocpOperation* operation, const std::size_t bytesTransferred)
		{
			spdlog::info("pqcs test");
		}, nullptr);

	::PostQueuedCompletionStatus(mIocpHandle, 0, 0, operation);
}

