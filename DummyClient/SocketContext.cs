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
        public bool Connected => Socket?.Connected ?? false;
        private volatile Socket? Socket;
        private readonly Client Client;

        private readonly byte[] SendBuffer;
        private readonly byte[] RecvBuffer;
        private readonly BinaryWriter BinaryWriter;
        private readonly BinaryReader BinaryReader;

        public SocketContext(Client owner)
        {
            Client = owner;
            SendBuffer = new byte[65536];
            RecvBuffer = new byte[65536];
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
            if (Socket == null)
            {
                return;
            }

            try
            {
                // MakePacket
                string packetEnumStr = packet.Descriptor.Name;
                var packetId = (Protocol.ProtocolEnum) Enum.Parse(typeof(Protocol.ProtocolEnum), packetEnumStr);

                var size = (short) packet.CalculateSize();
                byte[] sendBuffer = new byte[size + 4];
                Array.Copy(BitConverter.GetBytes(size + 4), 0, sendBuffer, 0, sizeof(ushort));
                Array.Copy(BitConverter.GetBytes((ushort)packetId), 0, sendBuffer, 2, sizeof(ushort));
                Array.Copy(packet.ToByteArray(), 0, sendBuffer, 4, size);
                
                SocketError errorCode;

                try
                {
                    Socket.Send(sendBuffer, 0, sendBuffer.Length, SocketFlags.None, out errorCode);
                }
                catch (ObjectDisposedException)
                {
                    Console.WriteLine("Socket has already disposed. failed to send packet.");
                    return;
                }

                if (errorCode != SocketError.Success)
                {
                    Console.WriteLine($"SendPacket failed: errorCode: {errorCode}");
                }
            } 
            catch (Exception e)
            {
                Console.WriteLine($"SendPacket::Unexpected exception: {e}");
                throw;
            }
        }

        public void StartReceive()
        {
        }
    }
}
