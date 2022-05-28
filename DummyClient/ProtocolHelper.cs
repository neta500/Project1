using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DummyClient.Protocol;

namespace DummyClient
{
    public static class ProtocolHelper
    {
        private static readonly Dictionary<ProtocolEnum, Google.Protobuf.IMessage> ProtocolTypeMap;

        static ProtocolHelper()
        {
            Type[] packetTypes = typeof(Google.Protobuf.IMessage)
                .Assembly
                .GetTypes()
                .Where(t => typeof(Google.Protobuf.IMessage).IsAssignableFrom(t) && t.IsAbstract == false)
                .ToArray();

            var types = typeof(Google.Protobuf.IMessage).Assembly;
            var typesTemplate = typeof(Google.Protobuf.IMessage<>).Assembly;

            var move = 

            ProtocolTypeMap = new Dictionary<ProtocolEnum, Google.Protobuf.IMessage>();
        }

        public static void Initialize()
        {
            Console.WriteLine("ProtocolHelper init");
        }

        public static Type? GetPacketType(ProtocolEnum packetEnum)
        {
            ProtocolTypeMap.TryGetValue(packetEnum, out var packetType);
            return null;
        }
    }
}
