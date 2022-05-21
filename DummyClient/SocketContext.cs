using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using Google.Protobuf;

namespace DummyClient
{
    internal class SocketContext
    {
        public bool Connected;
        private Socket Socket;
        private readonly Client Client;

        private readonly Byte[] SendBuffer;
        private readonly Byte[] RecvBuffer;
        private readonly BinaryWriter BinaryWriter;
        private readonly BinaryReader BinaryReader;

        public SocketContext(Client owner)
        {
            Client = owner;
            SendBuffer = new Byte[65536];
            RecvBuffer = new Byte[65536];
        }

        public bool Connect(string addr, int port)
        {
            Debug.Assert(Socket == null);

            IPAddress address = Dns.GetHostAddresses(addr)[0];
            IPEndPoint endPoint = new IPEndPoint(address, port);

            Socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            Socket.NoDelay = true;

            try
            {
                Socket.Connect(endPoint);
                Socket.Blocking = false;
                return true;
            }
            catch (Exception e)
            {
                Console.WriteLine($"Socket connect failed: {e} {addr} {port}");
                return false;
            }
        }

        public void Disconnect()
        {
            if (Socket == null)
            {
                return;
            }

            try
            {
                Socket.Shutdown(SocketShutdown.Both);
            }
            catch (Exception e)
            {
                Console.WriteLine($"Socket shutdown failed: {e}");
            }

            Socket.Dispose();
            Socket = null;
        }

        public void SendPacket(Google.Protobuf.IMessage packet)
        {
            Socket copySocket = Socket;
            if (copySocket == null)
            {
                return;
            }

            try
            {
                if (copySocket == null)
                {
                    Console.WriteLine($"Socket {copySocket.Handle} not connected");
                    return;
                }

                
            }
            catch (Exception e)
            {
                Console.WriteLine($"SendPacket::Unexpected exception: {e}");
                throw;
            }
        }
    }
}
