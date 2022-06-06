using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using Protocol;

namespace DummyClient;

using System.Net.Sockets;
using System.Net;

public class Program
{
    public static void Main()
    {
        ServerPacketHandler.Instance.Initialize();
        
        Thread.Sleep(5000);

        Bot bot = new Bot();
        bot.ConnectToServer();

        while (true)
        {
            Thread.Sleep(100);
            if (bot.Connected)
            {
                bot.SendPacket(new C_TEST
                {
                    Id = (ulong)Random.Shared.NextInt64(100)
                });
            }
        }
    }
}

