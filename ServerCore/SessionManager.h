#pragma once
#include <set>
#include "Session.h"
#include "SpinLock.h"

class SessionManager
{
public:
	static constexpr int DefaultSessionCount = 5000;

public:
	SessionManager(const IoContext& ioContext, ServerService& serverService, const int sessionCount)
		: _poolCount(sessionCount)
	{
		_sessionList.reserve(sessionCount);

		for (int i = 0; i < sessionCount; ++i)
		{
			_sessionList.emplace_back(std::make_shared<Session>(ioContext, serverService));
		}
	}

	std::shared_ptr<Session> AcquireSession()
	{
		WRITE_LOCK;

		++_popIndex;
		const int index = _popIndex % _poolCount;
		const auto& session = _sessionList[index];
		_sessionList[index] = nullptr;

		_aliveSessionList.emplace(session);
		return session;
	}

	void ReleaseSession(const std::shared_ptr<Session>& session)
	{
		WRITE_LOCK;

		++_pushIndex;
		const int index = _pushIndex % _poolCount;
		_sessionList[index] = session;
		_aliveSessionList.erase(session);
	}

	USE_LOCK;

	const int _poolCount;
	int _pushIndex = 0;
	int _popIndex = 0;

	std::vector<std::shared_ptr<Session>> _sessionList{};
	std::set<std::shared_ptr<Session>> _aliveSessionList{};
};
