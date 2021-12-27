#pragma once
#include <atomic>

class SpinLock
{
	static constexpr int MaxSpinCount = 5000;
	static constexpr int LockTimeOut = 120000;

	enum Flag: unsigned int
	{
		WriteLock = 0xFFFF'0000,
		ReadLock = 0x0000'FFFF,
		Empty = 0x0000'0000
	};

public:
	void WriteLock();
	void WriteUnLock();
	void ReadLock();
	void ReadUnLock();

private:
	std::atomic<unsigned int> mLockFlag = Flag::Empty;
	std::atomic<unsigned int> mWriteLockCount = 0;
	__int64 mLockAcquiredTick = 0;
};