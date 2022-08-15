#pragma once
#include "Acceptor.h"
#include "IoContext.h"
#include "Session.h"
#include "SessionManager.h"

class ServerService
{
public:
	ServerService(IoContext& ioContext, const EndPoint& endPoint)
		: _ioContext(ioContext),
		  _acceptor(ioContext, endPoint, this),
		  _sessionManager(ioContext, *this, SessionManager::DefaultSessionCount)
	{		
	}

	~ServerService()
	{
		spdlog::info("ServerService destructor");
	}
	
	std::shared_ptr<Session> AcquireSession()
	{
		return _sessionManager.AcquireSession();
	}

	void ReleaseSession(const std::shared_ptr<Session>& session)
	{
		_sessionManager.ReleaseSession(session);
	}

	void Start()
	{
		_acceptor.Accept();
	}
	
	IoContext& _ioContext;
	Acceptor _acceptor;
	SessionManager _sessionManager;
};
