using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DummyClient
{
    public delegate void PacketEvent(Bot bot, Google.Protobuf.IMessage packet);

    public class Bot
    {
        private readonly SocketContext ServerContext;

        public event PacketEvent PacketHandler;
    }
}
