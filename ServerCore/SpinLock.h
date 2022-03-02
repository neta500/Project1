#pragma once

// recurrsive read-write spinlock
// forbidden : read -> write lock in same thread context
// [WWWWWWWW][WWWWWWWW][RRRRRRRR][RRRRRRRR]
// [     2 Bytes      ][     2 Bytes      ]
// [  Write Thread Id ][    Read Count    ]              

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
		// 스레드가 writelock했을때랑 반대로 연산해주면 thread id가 나온다
		return (mLockFlag.load() & LockFlag::WriteLockFlag) >> 16;
	}

	bool ReadLocked() const
	{
		// readlock은 mLockFlag의 뒤 2바이트를 사용하므로, ReadLockFlag(0x0000FFFF)과
		// & 연산을 해주면 앞의 2바이트는 다 날라가고, 뒤 2바이트인 ReadLockCount만 남는다.
		return (mLockFlag.load() & LockFlag::ReadLockFlag) != 0;
	}

	auto GetReadLockCount() const
	{
		// 뒤 2바이트는 ReadLockCount이므로, 0x0000FFFF와 & 연산하면 뒤 2바이트만 뽑힌다.
		return mLockFlag.load() & LockFlag::ReadLockFlag;
	}

	uint32 WriteLockedFlag() const
	{
		// 앞의 2바이트는 writelock 잡은 스레드의 id가 차지한다.
		return LThreadId << 16 & LockFlag::WriteLockFlag;
	}
	
	std::atomic<uint32> mLockFlag = LockFlag::Empty;
	std::atomic<int32> mWriteLockCount = 0;
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