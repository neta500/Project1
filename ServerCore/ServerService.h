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
	}

	~ServerService()
	{
		spdlog::info("ServerService destructor");
	}

	void SetSession(std::shared_ptr<Session> session)
	{
		mSession = session;
	}

	std::shared_ptr<Session> GetSession() const { return mSession; }

	void Start()
	{
		mAcceptor.Accept();
	}
	
	IoContext& mIoContext;
	Acceptor mAcceptor;
	std::shared_ptr<Session> mSession = nullptr;
};