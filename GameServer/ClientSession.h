#pragma once
#include "Session.h"
#include <spdlog/spdlog.h>
#include "Protocol.pb.h"
#include "SendBuffer.h"

class ClientSession : public PacketSession
{
public:
	explicit ClientSession(const IoContext& ioContext)
		: PacketSession(ioContext)
	{		
	}
	~ClientSession() override = default;

	int OnRecvPacket(const std::byte* recvBuffer, const int len) override
	{
		const PacketHeader* header = reinterpret_cast<const PacketHeader*>(recvBuffer);
		const auto recvStr = mRecvBuffer.GetRecvString(mRecvBuffer.DataSize());
		spdlog::info("Recv {} - {}", recvStr.size(), recvStr);
		const auto sendBuffer = std::make_shared<SendBuffer>(static_cast<int>(recvStr.size() + 1));
		sendBuffer->CopyData(recvStr.data(), static_cast<int>(recvStr.size()));
		BeginSend(sendBuffer);

		return static_cast<int>(recvStr.size());
	}

};