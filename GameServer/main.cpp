#include "pch.h"
#include <iostream>
#include <SpinLock.h>

class TestLock
{
public:
	int Read()
	{
		ReadScopedLock<SpinLock> lock(mLock);
		//std::scoped_lock<std::mutex> lock(mMutex);

		if (mQueue.empty())
		{
			return -1;
		}

		return mQueue.front();
	}

	void Write()
	{
		WriteScopedLock<SpinLock> lock(mLock);
		//std::scoped_lock<std::mutex> lock(mMutex);
		mQueue.push(std::rand() % 100);
	}

	void Pop()
	{
		WriteScopedLock<SpinLock> lock(mLock);
		//std::scoped_lock<std::mutex> lock(mMutex);
		if (mQueue.empty() == false)
		{
			mQueue.pop();
		}
	}

	std::queue<int> mQueue;
	SpinLock mLock;
	std::mutex mMutex;
};

TestLock test;

void ThreadWrite()
{
	while (true)
	{
		test.Write();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		test.Pop();
	}
}

void ThreadRead()
{
	while (true)
	{
		const auto value = test.Read();
		spdlog::info("{}", value);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main()
{
	std::jthread t1(ThreadWrite);
	std::jthread t2(ThreadWrite);
	std::jthread t3(ThreadRead);
	std::jthread t4(ThreadRead);
	std::jthread t5(ThreadRead);
	std::jthread t6(ThreadRead);
	std::jthread t7(ThreadRead);

	return 0;
}