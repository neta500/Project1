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
	unsigned short mWriteLockCount = 0;
	__int64 mLockAcquiredTick = 0;
};

template <class _Lock>
class ReadScopedLock
{
public:
	explicit ReadScopedLock(_Lock& lock) : mLock(lock)
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
	_Lock& mLock;
};

template <class _Lock>
class WriteScopedLock
{
public:
	explicit WriteScopedLock(_Lock& lock) : mLock(lock)
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
	_Lock& mLock;
};