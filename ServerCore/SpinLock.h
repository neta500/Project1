#pragma once

// write -> write ( o )
// write -> read ( o )
// read -> write ( x )

class SpinLock
{
	static constexpr int MaxSpinCount = 5000;
	static constexpr int LockTimeOut = 12000;

	enum LockFlag: unsigned int
	{
		WriteLockFlag = 0xFFFF'0000,
		ReadLockFlag = 0x0000'FFFF,
		Empty = 0x0000'0000
	};

public:
	SpinLock() = default;
	~SpinLock() = default;

	void WriteLock();
	void WriteUnLock();
	void ReadLock();
	void ReadUnLock();

private:
	std::atomic<unsigned int> mLockFlag = LockFlag::Empty;
	unsigned short mWriteLockCount = 0;
	__int64 mLockAcquiredTick = 0;
};

template <class Lock>
class ReadScopedLock
{
public:
	explicit ReadScopedLock(Lock& lock) : mLock(lock)
	{
		mLock.ReadLock();
	}

	~ReadScopedLock() noexcept
	{
		mLock.ReadUnLock();
	}

	ReadScopedLock(const ReadScopedLock&) = delete;
	ReadScopedLock& operator=(const ReadScopedLock&) = delete;

private:
	Lock& mLock;
};

template <class Lock>
class WriteScopedLock
{
public:
	explicit WriteScopedLock(Lock& lock) : mLock(lock)
	{
		mLock.WriteLock();
	}

	~WriteScopedLock() noexcept
	{
		mLock.WriteUnLock();
	}

	WriteScopedLock(const WriteScopedLock&) = delete;
	WriteScopedLock& operator=(const WriteScopedLock&) = delete;

private:
	Lock& mLock;
};

#define USE_LOCK mutable SpinLock mLock
#define READ_LOCK ReadScopedLock<SpinLock> readLock(mLock)
#define WRITE_LOCK WriteScopedLock<SpinLock> writeLock(mLock)