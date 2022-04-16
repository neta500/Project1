#pragma once
#include <functional>

class ClientSession;
using PacketHandlerFunc = std::function<bool(std::shared_ptr<ClientSession>, std::byte*, int)>;
inline PacketHandlerFunc GPacketHandler[65536];

class ClientPacketHandler
{
public:

};
