#pragma once
#include "Singleton.h"
#include "Timer.h"

static void InitThreadLocal(const uint32 threadId)
{
	spdlog::info("ThreadLocal init: {}", threadId);
	LThreadId = threadId;
	LTimer = new Timer();
}

class ThreadManager
{
public:
	static ThreadManager& GetInstance()
	{
		static ThreadManager instance;
		return instance;
	}

	template <class Fn, class ...Args, std::enable_if_t<!std::is_same_v<std::remove_cvref_t<Fn>, std::jthread>, int> = 0>
	void MakeThread(Fn&& func, Args&&... args)
	{
		std::scoped_lock lock(mLock);

		mThreads.emplace_back(std::thread([=, this]()
			{
				InitThreadLocal(++mThreadCount);
				func(args...);
			}));
	}

	void JoinAll()
	{
		for (auto& thread : mThreads)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}
	}

private:
	ThreadManager() = default;
	~ThreadManager() = default;

	std::mutex mLock;
	std::atomic<int> mThreadCount = 0;
	std::vector<std::thread> mThreads;
};
