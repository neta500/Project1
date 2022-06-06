using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Protocol;

namespace DummyClient
{
    public delegate void PacketEvent(Bot bot, Google.Protobuf.IMessage packet);

    public class Bot
    {
        public bool Connected => ServerContext.Connected;
        private readonly SocketContext ServerContext;
        public readonly BotManager BotManager;

        public event PacketEvent PacketHandler;

        public Bot()
        {
            ServerContext = new SocketContext(this);
            PacketHandler += Bot_PacketReceiveHandler;
            ServerContext.Callback = PacketCallback;
        }

        private void Bot_PacketReceiveHandler(Bot sender, Google.Protobuf.IMessage recvPacket)
        {
            if (recvPacket is S_TEST packet)
            {
                Console.WriteLine($"S_TEST: {packet.Id}, {packet.Hp}, {packet.Attack}");
            }
        }

        private void PacketCallback(Google.Protobuf.IMessage packet)
        {
            PacketHandler.Invoke(this, packet);
        }

        public void ConnectToServer()
        {
            ServerContext.Connect("127.0.0.1", 712);
        }

        public void Disconnect()
        {
            ServerContext.Disconnect();
        }

        public void SendPacket(Google.Protobuf.IMessage packet)
        {
            ServerContext.SendPacket(packet);
        }
    }
}
