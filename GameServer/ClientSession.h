#pragma once
#include "Session.h"
#include <spdlog/spdlog.h>
#include "Protocol.pb.h"
#include "SendBuffer.h"

class ClientSession : public Session
{
public:
	explicit ClientSession(const IoContext& ioContext)
		: Session(ioContext)
	{		
	}
	~ClientSession() override = default;

	int OnRecv(const std::byte* recvBuffer, const int len) override
	{
		const auto recvStr = mRecvBuffer.GetRecvString(mRecvBuffer.DataSize());
		spdlog::info("Recv {} - {}", recvStr.size(), recvStr);
		const auto sendBuffer = std::make_shared<SendBuffer>(static_cast<int>(recvStr.size() + 1));
		sendBuffer->CopyData(recvStr.data(), static_cast<int>(recvStr.size()));
		BeginSend(sendBuffer);

		return static_cast<int>(recvStr.size());
	}

};