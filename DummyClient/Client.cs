using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

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
                    var sendMsg = GetRandomString(Random.Next(5, 50));
                    Console.WriteLine("Send {0} - {1}", sendMsg.Length, sendMsg);
                    Socket.Send(Encoding.ASCII.GetBytes(sendMsg));
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
    }
}
