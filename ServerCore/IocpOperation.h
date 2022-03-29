#pragma once
#include <minwinbase.h>

class Session;

enum class IoType
{
	Send,
	Recv,
	Accept,
	Connect,
	Disconnect
};

class IocpOperation : public OVERLAPPED
{
	using FuncType = std::function<void(IocpOperation*, std::size_t)>;
public:
	IocpOperation(const IoType ioType, const FuncType func, const std::shared_ptr<Session> session)
		: _OVERLAPPED{}, mIoType(ioType), mFunc(func), mSession(session)
	{
		OVERLAPPED::hEvent = nullptr;
		OVERLAPPED::Internal = 0;
		OVERLAPPED::InternalHigh = 0;
		OVERLAPPED::Offset = 0;
		OVERLAPPED::OffsetHigh = 0;
		OVERLAPPED::Pointer = nullptr;
	}

	~IocpOperation()
	{
		spdlog::info("IocpOperation destructor");
	}
	
	void Complete(const std::size_t bytesTransferred)
	{
		mFunc(this, bytesTransferred);
	}

	std::shared_ptr<Session> GetSession() const { return mSession; }

private:
	IoType mIoType;
	FuncType mFunc;
	std::shared_ptr<Session> mSession;
};

