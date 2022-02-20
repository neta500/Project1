#pragma once

// recurrsive read-write spinlock
// forbidden : read -> write lock in same thread context

class SpinLock
{
	static constexpr int MaxSpinCount = 5000;
	static constexpr int LockTimeOut = 12000;

	enum LockFlag: uint32
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
	auto GetOwnerThreadId() const
	{
		return (mLockFlag.load() & LockFlag::WriteLockFlag) >> 16;
	}

	bool ReadLocked() const
	{
		return (mLockFlag.load() & LockFlag::ReadLockFlag) != 0;
	}

	auto GetReadLockCount() const
	{
		return mLockFlag.load() & LockFlag::ReadLockFlag;
	}

	uint32 WriteLockedFlag() const
	{
		return LThreadId << 16 & LockFlag::WriteLockFlag;
	}
	
	std::atomic<uint32> mLockFlag = LockFlag::Empty;
	std::atomic<uint16> mWriteLockCount = 0;
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