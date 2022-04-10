#pragma once
#include <vector>

class RecvBuffer
{
	constexpr static int BufferCount = 10;
public:
	explicit RecvBuffer(const int size) : mCapacity(size * BufferCount), mBufferSize(size)
	{
		mRecvBuffer.resize(mCapacity);
	}

	~RecvBuffer() = default;

	void Clean()
	{
		if (const int dataSize = DataSize(); dataSize == 0)
		{
			mReadPos = 0;
			mWritePos = 0;
		}
		else
		{
			if (FreeSize() < mBufferSize)
			{
				::memcpy(&mRecvBuffer[0], &mRecvBuffer[mReadPos], dataSize);
				mReadPos = 0;
				mWritePos = dataSize;
			}			
		}
	}

	bool OnRead(const int readBytes)
	{
		if (readBytes > DataSize())
		{
			return false;
		}

		mReadPos += readBytes;
		return true;
	}

	bool OnWrite(const int writeBytes)
	{
		if (writeBytes > FreeSize())
		{
			return false;
		}

		mWritePos += writeBytes;
		return true;
	}

	// test
	std::string GetRecvString(const int byteTransferred) const
	{		
		return std::string(reinterpret_cast<const char*>(&mRecvBuffer[mReadPos]), byteTransferred);
	}

	std::byte* ReadPos() { return &mRecvBuffer[mReadPos]; }
	std::byte* WritePos() { return &mRecvBuffer[mWritePos]; }
	int DataSize() const { return mWritePos - mReadPos; }
	int FreeSize() const { return mCapacity - mWritePos; }

private:
	int mCapacity = 0;
	int mBufferSize = 0;
	int mReadPos = 0;
	int mWritePos = 0;
	std::vector<std::byte> mRecvBuffer{};
};