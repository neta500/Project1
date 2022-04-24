// [Auto Generated File]

#pragma once
#include "Protocol.pb.h"
#include "Session.h"
#include "SendBuffer.h"

class ClientSession;
using PacketHandlerFunc = std::function<bool(std::shared_ptr<ClientSession>, std::byte*, int)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
{%- for pkt in parser.total_pkt %}
	PKT_{{pkt.name}} = {{pkt.id}},
{%- endfor %}
};

bool Handle_INVALID(std::shared_ptr<ClientSession> session, std::byte* buffer, int len);

{%- for pkt in parser.recv_pkt %}
bool Handle_{{pkt.name}}(std::shared_ptr<ClientSession> session, Protocol::{{pkt.name}}& pkt);
{%- endfor %}

class {{output}}
{
public:
	static void Init()
	{
		for (auto i = 0; i < UINT16_MAX; ++i)
		{
			GPacketHandler[i] = Handle_INVALID;
		}


{%- for pkt in parser.recv_pkt %}
		GPacketHandler[static_cast<int>(PKT_{{pkt.name}})] = [](std::shared_ptr<ClientSession> session, std::byte* buffer, int len) { return HandlePacket<Protocol::{{pkt.name}}>(Handle_{{pkt.name}}, session, buffer, len); };
{%- endfor %}		
	}

	static void HandlePacket(std::shared_ptr<ClientSession> session, std::byte* buffer, int len)
	{
		const PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		GPacketHandler[header->mId](session, buffer, len);
	}


{%- for pkt in parser.send_pkt %}
	static std::shared_ptr<SendBuffer> MakeSendBuffer(Protocol::{{pkt.name}}& pkt) { return MakeSendBuffer(pkt, PKT_{{pkt.name}}); }
{%- endfor %}

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
