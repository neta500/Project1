using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Google.Protobuf;
using Protocol;

namespace DummyClient
{
    class ServerPacketHandler
    {
        public static ServerPacketHandler Instance { get; } = new();

        private readonly Dictionary<ushort, Action<SocketContext, ArraySegment<byte>, ushort>> OnRecv = new();
        
        public void Initialize()
        {
            // TODO: 아 이거 어떡하지 
            OnRecv.Add((ushort)Protocol.ProtocolEnum.S_TEST, MakePacket<S_TEST>);
        }

        public void OnRecvPacket(SocketContext context, ArraySegment<byte> buffer)
        {
            if (buffer.Array == null)
            {
                return;
            }

            var packetSize = BitConverter.ToUInt16(buffer.Array, buffer.Offset);
            var packetId = BitConverter.ToUInt16(buffer.Array, buffer.Offset + 2);

            if (OnRecv.TryGetValue(packetId, out var action))
            {
                action.Invoke(context, buffer, packetSize);
            }
        }

        void MakePacket<T>(SocketContext context, ArraySegment<byte> buffer, ushort id)
            where T : Google.Protobuf.IMessage, new()
        {
            T packet = new();
            packet.MergeFrom(new Google.Protobuf.CodedInputStream(buffer.Array, buffer.Offset + 4, buffer.Count - 4));
            context.Callback.Invoke(packet);
        }
    }
}
