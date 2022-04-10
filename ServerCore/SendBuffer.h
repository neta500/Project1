#pragma once
#include <vector>

class SendBuffer
{
public:
	explicit SendBuffer(const int bufferSize) : mSendBuffer(bufferSize)
	{
		mSendBuffer.resize(bufferSize);
	}

	~SendBuffer() = default;

	std::byte* Buffer() { return mSendBuffer.data(); }
	int WriteSize() const { return mWriteSize; }
	int Capacity() const { return static_cast<int>(mSendBuffer.size()); }

	void CopyData(const void* data, const int length)
	{
		::memcpy(mSendBuffer.data(), data, length);
		mWriteSize = length;
	}

	int mWriteSize = 0;
	std::vector<std::byte> mSendBuffer{};
};