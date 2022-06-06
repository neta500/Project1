#include "pch.h"
#include "ClientPacketHandler.h"

#include "ClientSession.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(std::shared_ptr<ClientSession> session, std::byte* buffer, int len)
{
	return false;
}

bool Handle_C_TEST(std::shared_ptr<ClientSession> session, Protocol::C_TEST& pkt)
{
	spdlog::info("C_TEST id: {}", pkt.id());

	Protocol::S_TEST sendPacket;
	sendPacket.set_id(pkt.id());
	sendPacket.set_attack(11);
	sendPacket.set_hp(1000);
	session->Send(sendPacket);

	return true;
}

bool Handle_C_MOVE(std::shared_ptr<ClientSession> session, Protocol::C_MOVE& pkt)
{
	return false;
}
