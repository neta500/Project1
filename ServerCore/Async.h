#pragma once
#include "CoreTypeDefine.h"
#include "CoreThreadLocal.h"
#include "Job.h"
#include "Timer.h"
#include <mutex>
#include <queue>

// Async를 상속받는 클래스는 관련 비동기 함수 호출 가능
class Async
{
public:
	Async() = default;
	virtual ~Async() = default;

public:
	template <typename T, typename... Args>
	void DoAsync(void (T::* memFunc)(Args...), Args&&... args)
	{
		std::scoped_lock lock(_mutex);
		_queue.push(std::make_shared<Job>(static_cast<T*>(this), memFunc, std::forward<Args>(args)...));
	}

	void Execute()
	{
		std::scoped_lock lock(_mutex);

		while (true)
		{
			std::vector<std::shared_ptr<Job>> jobs{};
			PopAll(jobs);

			for (const auto& job : jobs)
			{
				job->Execute();
			}

			if (_queue.size() == 0)
			{
				return;
			}
		}
	}

	template <class T, class... Args>
	void DoTimer(const uint32 after, void (T::*memFunc)(Args...), Args&&... args)
	{
		auto job = new Job(static_cast<T*>(this), memFunc, std::forward<Args>(args)...);
		LTimer->PushTimerJob(after, job);
	}

private:
	void PopAll(std::vector<std::shared_ptr<Job>>& jobs)
	{
		while (auto job = Pop())
		{
			jobs.push_back(job);
		}
	}

	std::shared_ptr<Job> Pop()
	{
		if (_queue.empty())
		{
			return nullptr;
		}

		std::shared_ptr<Job> job = _queue.front();
		_queue.pop();
		return job;
	}

private:
	std::mutex _mutex;
	std::queue<std::shared_ptr<Job>> _queue;
};
