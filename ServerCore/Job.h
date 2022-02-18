#pragma once
#include <functional>

class Job
{
public:
	Job() = default;

	template <class T, class... Args>
	Job(T* obj, void (T::* memFunc)(Args...), Args&&... args)
	{
		mFunc = [obj, memFunc, args...]
		{
			(obj->*memFunc)(args...);
		};

		SetCaller();
	}

	template <class T, class... Args>
	Job(std::shared_ptr<T> obj, void (T::* memFunc)(Args...), Args&&... args)
	{
		mFunc = [obj, memFunc, args...]
		{
			(obj.get()->*memFunc)(args...);
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
