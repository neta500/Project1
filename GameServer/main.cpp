#include "pch.h"
#include <Async.h>
#include <Job.h>
#include <random>
#include <ThreadManager.h>
#include <shared_mutex>
#include "BattlePassSeasonManager.h"

class TestClass : public Async
{
public:
	virtual ~TestClass()
	{
		spdlog::info("destructor TestClass");
	}

	void Test(int i)
	{
		spdlog::info("TestClass::Test {}", i);
	}

	void write()
	{
		std::mt19937_64 gen;
		std::uniform_int_distribution<int> dist(1, 9);
		for (int i = 0; i < 100000; ++i)
		{
			WRITE_LOCK;
			//std::unique_lock lock(mSharedMutex);
			a = dist(gen);
			b = dist(gen);
			c = a * b;
			//mLock.WriteUnLock();
		}

		c = -1;
	}

	void read()
	{
		while (true)
		{
			READ_LOCK;
			//std::shared_lock lock(mSharedMutex);
			//std::unique_lock u_lock(mSharedMutex);
			if (c < 0)
			{
				break;
			}
			if (c != a * b)
			{
				failed++;
			}
		}
	}

	USE_LOCK;
	std::mutex mMutex;
	std::shared_mutex mSharedMutex;
	int a = 0;
	int b = 0;
	int c = 0;
	int failed;
};

void TestTimer()
{
	ThreadManager::GetInstance().MakeThread([]()
		{
			auto testClass = new TestClass();
			testClass->DoTimer(3000, &TestClass::Test, 5);

			auto battlePassSeasonManager = new BattlePassSeasonManager();
			battlePassSeasonManager->LoadManager();
			battlePassSeasonManager->StartManager();

			while (true)
			{
				LTimer->Run();
			}
		});
}

int main()
{
	spdlog::info("init spdlog");

	// TestLock
	auto start = std::chrono::high_resolution_clock::now();
	auto testClass = new TestClass();

	ThreadManager::GetInstance().MakeThread([testClass]()
		{
			testClass->write();
		});

	for (int i = 0; i < 7; ++i)
	{
		ThreadManager::GetInstance().MakeThread([testClass]()
			{
				testClass->read();
			});
	}
	
	ThreadManager::GetInstance().JoinAll();
	
	auto stop = std::chrono::high_resolution_clock::now();
	const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
	spdlog::info("failed: {} elapsed: {}", testClass->failed, elapsed);

	return 0;
}
