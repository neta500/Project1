#pragma once
#include <functional>

class Job
{
public:
	template <typename T, typename... Args>
	Job(T* obj, void (T::* memFunc)(Args...), Args&&... args)
	{
		mFunc = [obj, memFunc, args...]
		{
			(obj->*memFunc)(args...);
		};

		SetCaller();
	}

	virtual ~Job() = default;

	virtual void Execute()
	{
		mFunc();
	}

private:
	void SetCaller()
	{
		CaptureStackBackTrace(4 - 1, 1, mCaller, nullptr);
	}

	std::function<void()> mFunc;
	void* mCaller[1];
};
