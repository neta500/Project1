#include "pch.h"
#include "ClientPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(std::shared_ptr<ClientSession> session, std::byte* buffer, int len)
{
	return false;
}

bool Handle_S_TEST(std::shared_ptr<ClientSession> session, Protocol::S_TEST& pkt)
{
	return false;
}
