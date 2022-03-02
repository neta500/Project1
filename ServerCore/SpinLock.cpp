#include "pch.h"	
#include "SpinLock.h"
#include "CoreThreadLocal.h"

void SpinLock::WriteLock()
{
	if (GetOwnerThreadId() == LThreadId)
	{
		++mWriteLockCount;
		return;
	}
	
	const auto desired = WriteLockedFlag();
	const auto beginTick = ::GetTickCount64();

	while (true)
	{
		for (int spinCount = 0; spinCount < MaxSpinCount; ++spinCount)
		{
			uint32 expected = LockFlag::Empty;
			if (mLockFlag.compare_exchange_strong(expected, desired))
			{
				++mWriteLockCount;
				return;
			}
		}
				
		if (::GetTickCount64() - beginTick > LockTimeOut)
		{
			util::Crash("lock timeout. may be readlocked");
		}

		std::this_thread::yield();		
	}
}

void SpinLock::WriteUnLock()
{
	if (ReadLocked())
	{
		util::Crash("invalid lock order (WriteUnLock on ReadLock");
	}

	const int32 count = --mWriteLockCount;
	if (count == 0)
	{
		mLockFlag.store(LockFlag::Empty);
		return;
	}

	if (count < 0)
	{
		util::Crash("multiple write unlock");
	}
}

void SpinLock::ReadLock()
{
	if (GetOwnerThreadId() == LThreadId)
	{
		mLockFlag.fetch_add(1);
		return;
	}

	const auto beginTick = ::GetTickCount64();
	while (true)
	{
		for (int spinCount = 0; spinCount < MaxSpinCount; ++spinCount)
		{
			uint32 expected = GetReadLockCount();
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
	if (false == ReadLocked())
	{
		util::Crash("multiple read unlock");
	}

	mLockFlag.fetch_sub(1);
}