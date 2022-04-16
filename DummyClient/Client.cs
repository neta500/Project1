using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Threading.Tasks;
using Google.Protobuf.Collections;
using Protocol;
using System.Runtime.Serialization;
using Google.Protobuf;

namespace DummyClient
{
    internal class Client
    {
        private readonly Socket Socket;
        private readonly byte[] RecvBuffer = new byte[1024];
        private readonly Random Random = new Random();

        public Client()
        {
            Socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP);
        }

        public void Connect()
        {
            try
            {
                Socket.Connect(new IPEndPoint(IPAddress.Loopback, 712));
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Thread.Sleep(1000);
                Connect();
            }
        }

        public void Disconnect()
        {
            Socket.Disconnect(true);
        }

        public void Run()
        {
            Connect();

            Socket.BeginReceive(RecvBuffer, 0, RecvBuffer.Length, SocketFlags.None, ReceiveCallback, Socket);
            
            while (true)
            {
                for (int count = 0; count <= 100; count++)
                {
                    var packet = GetTestPacket();
                    var str = packet.ToString();
                    var serialized = packet.ToByteArray();
                    Console.WriteLine("Send {0} - {1}", packet.CalculateSize(), str);
                    Socket.Send(serialized);
                    Thread.Sleep(500);
                }

                //Disconnect();
                //Thread.Sleep(1000);
                //Connect();
            }
        }

        private void ReceiveCallback(IAsyncResult result)
        {
            if (Socket.Connected)
            {
                var str = Encoding.ASCII.GetString(RecvBuffer);
                var length = Socket.EndReceive(result);

                Console.WriteLine("Recv {0} - {1}", length, str);
                Array.Clear(RecvBuffer);
                Socket.BeginReceive(RecvBuffer, 0, RecvBuffer.Length, SocketFlags.None, ReceiveCallback, Socket);
            }
        }

        public string GetRandomString(int len)
        {
            Random rand = new Random();
            string input = "abcdefghijklmnopqrstuvwxyz0123456789";

            var chars = Enumerable.Range(0, len)
                .Select(x => input[rand.Next(0, input.Length)]);
            return new string(chars.ToArray());
        }

        public Protocol.S_TEST GetTestPacket()
        {
            var packet = new Protocol.S_TEST
            {
                Attack = (uint) Random.Next(100),
                Hp = (uint) Random.Next(1000),
                Id = (uint) Random.Next(10)
            };

            var buffDataList = new List<BuffData>();

            for (int i = 0; i < 3; ++i)
            {
                var buffData = new BuffData
                {
                    BuffId = Random.NextInt64(500),
                    RemainTime = Random.NextInt64(400000, 500000)
                };

                buffData.Victims.Add((ulong) Random.NextInt64(100));
                buffData.Victims.Add((ulong)Random.NextInt64(100));
                buffData.Victims.Add((ulong)Random.NextInt64(100));
                buffDataList.Add(buffData);
            }

            packet.Buffs.AddRange(buffDataList);

            return packet;
        }
    }
}
