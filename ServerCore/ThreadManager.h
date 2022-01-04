#pragma once
#include "Singleton.h"

static void InitThreadLocal(const unsigned int threadId)
{
	spdlog::info("ThreadLocal init: {}", threadId);
	LThreadId = threadId;
}

class ThreadManager : public Singleton<ThreadManager>
{
public:
	ThreadManager(token) {}
	~ThreadManager() = default;

	template <class _Fn, class ..._Args, std::enable_if_t<!std::is_same_v<std::remove_cvref_t<_Fn>, std::jthread>, int> = 0>
	void MakeThread(_Fn&& func, _Args&&... args)
	{
		std::scoped_lock lock(mLock);

		mThreads.emplace_back(std::jthread([=, this]()
			{
				InitThreadLocal(++mThreadCount);
				func(args...);
			}));
	}	

	std::mutex mLock;
	std::atomic_int mThreadCount = 0;
	std::vector<std::jthread> mThreads;
};
