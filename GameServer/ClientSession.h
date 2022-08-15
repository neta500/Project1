#pragma once
#include "Session.h"
#include <spdlog/spdlog.h>
#include "Protocol.pb.h"
#include "SendBuffer.h"
#include "ClientPacketHandler.h"

class ClientSession : public PacketSession
{
public:
	explicit ClientSession(const IoContext& ioContext, ServerService& serverService)
		: PacketSession(ioContext, serverService)
	{		
	}
	~ClientSession() override = default;

	void OnRecvPacket(std::byte* recvBuffer, const int len) override
	{
		ClientPacketHandler::HandlePacket(std::static_pointer_cast<ClientSession>(shared_from_this()), recvBuffer, len);		
	}

	void OnDisconnected() override {}
	void OnConnected() override {}

	template <typename PacketType>
	void Send(PacketType&& packet)
	{
		BeginSend(ClientPacketHandler::MakeSendBuffer(std::forward<PacketType&&>(packet)));
	}
};