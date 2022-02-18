#include "pch.h"
#include "Timer.h"
#include "Job.h"

Timer::Timer()
{
	mBeginTick = std::chrono::high_resolution_clock::now();
	LTickCount = GetCurrentTick();
}

void Timer::PushTimerJob(const uint32 after, Job* job)
{
	const int64 executeTick = LTickCount + after;
	mTimerQueue.push(TimerElem(job, executeTick));
}

void Timer::Run()
{
	LTickCount = GetCurrentTick();

	while (false == mTimerQueue.empty())
	{
		const TimerElem& timerElem = mTimerQueue.top();

		if (LTickCount < timerElem.mExecutionTick)
		{
			break;
		}

		timerElem.mJob->Execute();

		mTimerQueue.pop();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

int64 Timer::GetCurrentTick() const
{
	const auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(now - mBeginTick).count();
}
