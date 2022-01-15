#include "pch.h"	
#include "SpinLock.h"
#include "CoreTls.h"

void SpinLock::WriteLock()
{
	// 이미 같은 스레드가 잡고있으면 count만 올려준다.
	const auto lockThreadId = (mLockFlag.load(std::memory_order_relaxed) & LockFlag::WriteLockFlag) >> 16;
	if (lockThreadId == LThreadId)
	{
		mWriteLockCount++;
		return;
	}

	const auto desired = LThreadId << 16 & LockFlag::WriteLockFlag;
	const auto beginTick = ::GetTickCount64();

	while (true)
	{
		for (int spinCount = 0; spinCount < MaxSpinCount; ++spinCount)
		{
			unsigned int expected = LockFlag::Empty;
			if (mLockFlag.compare_exchange_strong(expected, desired, std::memory_order_acquire))
			{
				mWriteLockCount++;
				return;
			}
		}

		if (::GetTickCount64() - beginTick > LockTimeOut)
		{
			util::Crash("lock timeout");
		}

		std::this_thread::yield();		
	}
}

void SpinLock::WriteUnLock()
{
	if ((mLockFlag.load(std::memory_order_relaxed) & LockFlag::ReadLockFlag) != 0)
	{
		util::Crash("invalid lock order");
	}

	if (--mWriteLockCount == 0)
	{
		mLockFlag.store(LockFlag::Empty, std::memory_order_release);
	}
}

void SpinLock::ReadLock()
{
	// 이미 같은 스레드가 잡고있으면 count만 올려준다.
	const auto lockThreadId = (mLockFlag.load(std::memory_order_relaxed) & LockFlag::WriteLockFlag) >> 16;
	if (lockThreadId == LThreadId)
	{
		mLockFlag.fetch_add(1, std::memory_order_acquire);
		return;
	}

	const auto beginTick = ::GetTickCount64();
	while (true)
	{
		for (int spinCount = 0; spinCount < MaxSpinCount; ++spinCount)
		{
			unsigned int expected = mLockFlag.load() & LockFlag::ReadLockFlag;
			if (mLockFlag.compare_exchange_strong(expected, expected + 1, std::memory_order_acquire))
			{
				return;
			}
		}

		if (::GetTickCount64() - beginTick > LockTimeOut)
		{
			util::Crash("lock timeout");
		}

		std::this_thread::yield();
	}
}

void SpinLock::ReadUnLock()
{
	if ((mLockFlag.fetch_sub(1, std::memory_order_release) & LockFlag::ReadLockFlag) == 0)
	{
		util::Crash("multiple read unlock");
	}
}