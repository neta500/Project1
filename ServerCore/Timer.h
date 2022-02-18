#pragma once
#include <chrono>
#include "Job.h"

class Async;

class TimerElem
{
public:
	TimerElem() = default;
	TimerElem(Job* job, const int64 executionTick)
		: mJob(job), mExecutionTick(executionTick)
	{}

	Job* mJob;
	int64 mExecutionTick;
};

struct TimerJobComparator
{
	bool operator()(const TimerElem& left, const TimerElem& right) const
	{
		return left.mExecutionTick > right.mExecutionTick;
	}
};

class Timer
{
public:
	Timer();

	void PushTimerJob(const uint32 after, Job* job);
	void Run();

private:
	int64 GetCurrentTick() const;

	std::chrono::high_resolution_clock::time_point mBeginTick;
	std::priority_queue<TimerElem, std::vector<TimerElem>, TimerJobComparator> mTimerQueue;
};
