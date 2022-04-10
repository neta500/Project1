#pragma once
#include <minwinbase.h>

class Session;
class SendBuffer;

enum class IoType
{
	Send,
	Recv,
	Accept,
	Connect,
	Disconnect
};

namespace etos
{
	// TODO : use enum to string macro Ȥ�� �������
	constexpr std::string ToString(const IoType ioType) noexcept
	{
		switch(ioType)
		{
		case IoType::Connect: return "Connect";
		case IoType::Recv: return "Recv";
		case IoType::Accept: return "Accept";
		case IoType::Disconnect: return "Disconnect";
		case IoType::Send: return "Send";
		default: return "Invalid";
		}
	}
}

class IocpOperation : public OVERLAPPED
{
	using FuncType = std::function<void(IocpOperation* operation, std::size_t)>;
public:
	IocpOperation(const IoType ioType, const FuncType func, Session* session)
		: _OVERLAPPED{}, mIoType(ioType), mFunc(func), mSession(session)
	{
		spdlog::info("IocpOperation({}) constructor", etos::ToString(mIoType));

		OVERLAPPED::hEvent = nullptr;
		OVERLAPPED::Internal = 0;
		OVERLAPPED::InternalHigh = 0;
		OVERLAPPED::Offset = 0;
		OVERLAPPED::OffsetHigh = 0;
		OVERLAPPED::Pointer = nullptr;
	}

	~IocpOperation()
	{
		spdlog::info("IocpOperation({}) destructor", etos::ToString(mIoType));
	}
	
	void Complete(const std::size_t bytesTransferred)
	{
		mFunc(this, bytesTransferred);
	}

	Session* GetSession() const { return mSession; }

public:
	// TODO : SendBufferQueue �۾�. ������ �ӽ÷� ���۸� ���� �Ҵ��ؼ� �����͸� �����
	std::vector<std::shared_ptr<SendBuffer>> mSendBufferVec{};

private:
	IoType mIoType;
	FuncType mFunc;
	Session* mSession;	
};

