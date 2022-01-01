#include "pch.h"	
#include "SpinLock.h"
#include "CoreTls.h"

void SpinLock::WriteLock()
{
	// 이미 같은 스레드가 잡고있으면 count만 올려준다.
	const auto lockThreadId = (mLockFlag.load() & LockFlag::WriteLockFlag) >> 16;
	if (lockThreadId == LThreadId)
	{
		mWriteLockCount++;
		return;
	}

	const auto desired = ((LThreadId << 16) & LockFlag::WriteLockFlag);
	const auto beginTick = ::GetTickCount64();

	while (true)
	{		
		unsigned int expected = LockFlag::Empty;

		for (int spinCount = 0; spinCount < MaxSpinCount; ++spinCount)
		{
			if (mLockFlag.compare_exchange_strong(expected, desired))
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
	if ((mLockFlag.load() & LockFlag::ReadLockFlag) != 0)
	{
		util::Crash("invalid lock order");
	}

	const auto lockCount = --mWriteLockCount;
	if (lockCount == 0)
	{
		mLockFlag = LockFlag::Empty;
	}
}

void SpinLock::ReadLock()
{
	// 이미 같은 스레드가 잡고있으면 count만 올려준다.
	const auto lockThreadId = (mLockFlag.load() & LockFlag::WriteLockFlag) >> 16;
	if (lockThreadId == LThreadId)
	{
		mLockFlag.fetch_add(1);
		return;
	}

	const auto beginTick = ::GetTickCount64();
	while (true)
	{
		unsigned int expected = mLockFlag.load() & LockFlag::ReadLockFlag;

		for (int spinCount = 0; spinCount < MaxSpinCount; ++spinCount)
		{
			if (mLockFlag.compare_exchange_strong(expected, expected + 1))
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
	if ((mLockFlag.fetch_sub(1) & LockFlag::ReadLockFlag) == 0)
	{
		util::Crash("multiple read unlock");
	}
}