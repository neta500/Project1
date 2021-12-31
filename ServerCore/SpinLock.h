#pragma once

// write -> write ( o )
// write -> read ( o )
// read -> write ( x )

class SpinLock
{
	static constexpr int MaxSpinCount = 5000;
	static constexpr int LockTimeOut = 120000;

	enum LockFlag: unsigned int
	{
		WriteLockFlag = 0xFFFF'0000,
		ReadLockFlag = 0x0000'FFFF,
		Empty = 0x0000'0000
	};

public:
	void WriteLock();
	void WriteUnLock();
	void ReadLock();
	void ReadUnLock();

private:
	std::atomic<unsigned int> mLockFlag = LockFlag::Empty;
	std::atomic<unsigned int> mWriteLockCount = 0;
	__int64 mLockAcquiredTick = 0;
};

class ReadScopedLock
{

};

class WriteScopedLock
{

};