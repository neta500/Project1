#pragma once
#include "Session.h"
#include <spdlog/spdlog.h>
#include "Protocol.pb.h"
#include "SendBuffer.h"
#include "ClientPacketHandler.h"

class ClientSession : public PacketSession
{
public:
	explicit ClientSession(const IoContext& ioContext)
		: PacketSession(ioContext)
	{		
	}
	~ClientSession() override = default;

	int OnRecvPacket(std::byte* recvBuffer, const int len) override
	{
		const auto recvStr = mRecvBuffer.GetRecvString(mRecvBuffer.DataSize());
		spdlog::info("Recv {} - {}", recvStr.size(), recvStr);
		const auto sendBuffer = std::make_shared<SendBuffer>(static_cast<int>(recvStr.size() + 1));
		sendBuffer->CopyData(recvStr.data(), static_cast<int>(recvStr.size()));
		BeginSend(sendBuffer);

		const PacketHeader* header = reinterpret_cast<const PacketHeader*>(recvBuffer);
		ClientPacketHandler::HandlePacket(std::static_pointer_cast<ClientSession>(shared_from_this()), recvBuffer, len);

		return static_cast<int>(recvStr.size());
	}

};