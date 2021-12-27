#include "SpinLock.h"
#include "CoreTls.h"
#include "pch.h"

void SpinLock::WriteLock()
{
	// �̹� ���� �����尡 ��������� count�� �÷��ش�.
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
				// ȹ�� ����
				mWriteLockCount++;
				return;
			}
		}

		// ȹ�� �����ϸ� �ٸ� �����忡�� �纸�Ѵ�.
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
