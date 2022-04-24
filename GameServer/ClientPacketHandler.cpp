#include "pch.h"
#include "ClientPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(std::shared_ptr<ClientSession> session, std::byte* buffer, int len)
{
	return false;
}

bool Handle_C_TEST(std::shared_ptr<ClientSession> session, Protocol::C_TEST& pkt)
{
	spdlog::info("C_TEST id: {}", pkt.id());

	// TODO : SEND TEST
	return true;
}

bool Handle_C_MOVE(std::shared_ptr<ClientSession> session, Protocol::C_MOVE& pkt)
{
	return false;
}
