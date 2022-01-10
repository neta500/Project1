#pragma once
#include <functional>

class Timer
{
public:
	void DoTimer(const int after, const std::function<void()>& func)
	{
		
	}

	template<typename T, typename Ret, typename... Args>
	void DoTimer(const int tickAfter, Ret(T::* memFunc)(Args...), Args... args)
	{
		
	}
};