#pragma once
#include "Acceptor.h"
#include "IoContext.h"
#include "Session.h"

class ServerService
{
public:
	ServerService(IoContext& ioContext, const EndPoint& endPoint)
		: mIoContext(ioContext), mAcceptor(ioContext, endPoint, this)
	{
		mSession = std::make_shared<Session>();
	}

	std::shared_ptr<Session> GetSession() const { return mSession; }

	void Start();
	
	IoContext& mIoContext;
	Acceptor mAcceptor;
	std::shared_ptr<Session> mSession = nullptr;
};