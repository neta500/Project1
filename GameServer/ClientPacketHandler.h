#pragma once
#include <functional>
#include <Session.h>
#include <SendBuffer.h>
#include "Protocol.pb.h"

class ClientSession;
using PacketHandlerFunc = std::function<bool(std::shared_ptr<ClientSession>, std::byte*, int)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
	PKT_S_TEST = 1,
	PKT_S_LOGIN = 2
};

bool Handle_INVALID(std::shared_ptr<ClientSession> session, std::byte* buffer, int len);
bool Handle_S_TEST(std::shared_ptr<ClientSession> session, Protocol::S_TEST& pkt);

class ClientPacketHandler
{
public:
	static void Init()
	{
		for (auto i = 0; i < UINT16_MAX; ++i)
		{
			GPacketHandler[i] = Handle_INVALID;
		}

		GPacketHandler[static_cast<int>(PKT_S_TEST)] = [](std::shared_ptr<ClientSession> session, std::byte* buffer, int len)
		{
			return HandlePacket<Protocol::S_TEST>(Handle_S_TEST, session, buffer, len);
		};
	}

	static void HandlePacket(std::shared_ptr<ClientSession> session, std::byte* buffer, int len)
	{
		const PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		GPacketHandler[header->mId](session, buffer, len);
	}

	static std::shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_TEST& pkt) { return MakeSendBuffer(pkt, PKT_S_TEST); }

private:
	template <typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, std::shared_ptr<ClientSession>& session, std::byte* buffer, int len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		{
			return false;
		}

		return func(session, pkt);
	}

	template <typename PacketType>
	static std::shared_ptr<SendBuffer> MakeSendBuffer(PacketType& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		auto sendBuffer = std::make_shared<SendBuffer>(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->mId = pktId;
		header->mSize = packetSize;

		if (false == pkt.SerializeToArray(&header[1], dataSize))
		{
			//spdlog::critical("MakePacket Failed");
			util::Crash("MakePacket Failed");
		}

		return sendBuffer;
	}
};
