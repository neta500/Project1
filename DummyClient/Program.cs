using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using Protocol;

namespace DummyClient;

using System.Net.Sockets;
using System.Net;

public class Program
{
    public static void Test(Bot bot)
    {
        bot.ConnectToServer();
        
        for (int i = 0; i < 10; i++)
        {
            Thread.Sleep(200);
            if (bot.Connected)
            {
                bot.SendPacket(new C_TEST
                {
                    Id = (ulong)Random.Shared.NextInt64(100)
                });
            }
        }

        bot.Disconnect();
    }

    public static void Main()
    {
        ServerPacketHandler.Instance.Initialize();
        
        Thread.Sleep(5000);

        Bot bot = new Bot();
        while (true)
        {
            Thread.Sleep(1000);
            Test(bot);
        }
    }
}

