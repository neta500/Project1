#pragma once
#include "CoreTypeDefine.h"
#include "CoreThreadLocal.h"
#include "Job.h"
#include "Timer.h"

// Async를 상속받는 클래스는 관련 비동기 함수 호출 가능
class Async
{
public:
	Async() = default;
	virtual ~Async() = default;

	template <class T, class... Args>
	void DoTimer(const uint32 after, void (T::*memFunc)(Args...), Args&&... args)
	{
		auto job = new Job(static_cast<T*>(this), memFunc, std::forward<Args>(args)...);
		LTimer->PushTimerJob(after, job);
	}
};
