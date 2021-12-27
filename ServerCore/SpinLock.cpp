#include "SpinLock.h"
#include "CoreTls.h"
#include "pch.h"

void SpinLock::WriteLock()
{
	// 이미 같은 스레드가 잡고있으면 count만 올려준다.
	const auto lockThreadId = mLockFlag.load() & Flag::WriteLock;
	if (lockThreadId == LThreadId)
	{
		mWriteLockCount++;
		return;
	}

	int spinCount = 0;
	const auto desired = ((LThreadId << 16) & Flag::WriteLock);

	while (true)
	{
		unsigned int expected = Flag::Empty;
		
		for (auto spinCount = 0; spinCount < MaxSpinCount; ++spinCount)
		{
			if (mLockFlag.compare_exchange_strong(expected, desired))
			{
				// 획득 성공
				mWriteLockCount++;
				return;
			}
		}

		// 획득 실패하면 다른 스레드에게 양보한다.
		std::this_thread::yield();
	}
}

void SpinLock::WriteUnLock()
{
}

void SpinLock::ReadLock()
{
}

void SpinLock::ReadUnLock()
{
}
