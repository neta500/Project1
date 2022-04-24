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

	void OnRecvPacket(std::byte* recvBuffer, const int len) override
	{
		const PacketHeader* header = reinterpret_cast<const PacketHeader*>(recvBuffer);
		ClientPacketHandler::HandlePacket(std::static_pointer_cast<ClientSession>(shared_from_this()), recvBuffer, len);		
	}

};