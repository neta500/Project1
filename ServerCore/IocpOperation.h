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