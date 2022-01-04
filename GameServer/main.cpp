#include "pch.h"
#include <iostream>
#include <SpinLock.h>
#include <ThreadManager.h>

class TestLock
{
public:
	int Read()
	{
		//ReadScopedLock<SpinLock> lock(mLock);
		//std::scoped_lock<std::mutex> lock(mMutex);

		std::shared_lock lock(mMutex);

		if (mQueue.empty())
		{
			return -1;
		}

		return mQueue.front();
	}

	void Write()
	{
		//WriteScopedLock<SpinLock> lock(mLock);
		//std::scoped_lock<std::mutex> lock(mMutex);
		std::unique_lock lock(mMutex);
		mQueue.push(std::rand() % 100);		
	}

	void Pop()
	{
		//WriteScopedLock<SpinLock> lock(mLock);
		//std::scoped_lock<std::mutex> lock(mMutex);
		std::unique_lock lock(mMutex);

		if (mQueue.empty() == false)
		{
			mQueue.pop();
		}
	}

	std::queue<int> mQueue;
	SpinLock mLock;
	std::shared_mutex mMutex;
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

void TestFunc(const std::string& str)
{
	spdlog::info("{}", str);
}

int main()
{
	spdlog::info("init spdlog");

	auto current = std::chrono::system_clock::now();
	auto current_utc = std::chrono::utc_clock::now();

	return 0;
}