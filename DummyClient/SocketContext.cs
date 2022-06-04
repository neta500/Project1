using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using Google.Protobuf;
using Protocol;
using System.Collections.Concurrent;

namespace DummyClient
{
    internal class SocketContext
    {
        private static readonly Thread[] ReceiveThreadList;
        private static readonly ConcurrentQueue<SocketContext> WaitingQueue;

        public bool Connected => Socket?.Connected ?? false;
        private volatile Socket? Socket;
        private readonly Bot Client;

        private readonly byte[] SendBuffer;
        private readonly byte[] RecvBuffer;
        private readonly BinaryWriter BinaryWriter;
        private readonly BinaryReader BinaryReader;

        private volatile bool IsReceiving;
        private volatile bool IsDisconnecting;

        private int ReceiveCount;

        private Action<Google.Protobuf.IMessage> Callback;

        static SocketContext()
        {
            int threadCount = 2 * Environment.ProcessorCount;

            ReceiveThreadList = new Thread[threadCount];
            for (int threadIndex = 0; threadIndex < threadCount; threadIndex++)
            {
                Thread thread = new Thread(GlobalReceiveLoop);
                thread.Start();
                thread.Priority = ThreadPriority.AboveNormal;
                thread.Name = $"Receiving Thread #{threadIndex + 1}";
                ReceiveThreadList[threadIndex] = thread;
            }

            WaitingQueue = new ConcurrentQueue<SocketContext>();
        }

        public SocketContext(Bot owner)
        {
            Client = owner;
            SendBuffer = new byte[65536];
            RecvBuffer = new byte[65536];

            IsReceiving = false;
            IsDisconnecting = false;

            ReceiveCount = 0;
            BinaryWriter = new BinaryWriter(new MemoryStream(SendBuffer, 0, SendBuffer.Length, true, true),
                Encoding.Unicode, true);
            BinaryReader = new BinaryReader(new MemoryStream(RecvBuffer, 0, RecvBuffer.Length, true, true),
                Encoding.Unicode, true);
        }

        private static void GlobalReceiveLoop()
        {

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
            Socket copiedSocket = Socket;
            if (copiedSocket == null)
                return;

            try
            {
                // MakePacket
                string packetEnumStr = packet.Descriptor.Name;

                var packetId = (Protocol.ProtocolEnum)Enum.Parse(typeof(Protocol.ProtocolEnum), packetEnumStr);
                var size = (short)packet.CalculateSize();

                lock (SendBuffer)
                {
                    Array.Copy(BitConverter.GetBytes(size + 4), 0, SendBuffer, 0, sizeof(ushort));
                    Array.Copy(BitConverter.GetBytes((ushort)packetId), 0, SendBuffer, 2, sizeof(ushort));
                    Array.Copy(packet.ToByteArray(), 0, SendBuffer, 4, size);

                    SocketError errorCode;

                    try
                    {
                        copiedSocket.Send(SendBuffer, 0, size, SocketFlags.None, out errorCode);
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
            } 
            catch (Exception e)
            {
                Console.WriteLine($"SendPacket::Unexpected exception: {e}");
                throw;
            }
        }

        public void StartReceive(Action<Google.Protobuf.IMessage> callback)
        {
            this.Callback = callback;

        }

        public Google.Protobuf.IMessage TryReceivePacket()
        {
            Socket copiedSocket = Socket;
            if (copiedSocket == null)
            {
                return null;
            }

            SocketError errorCode;

            while (ReceiveCount < 2)
            {
                int recv;
                try
                {
                    recv = copiedSocket.Receive(RecvBuffer, ReceiveCount, 2 - ReceiveCount, SocketFlags.None, out errorCode);
                }
                catch (ObjectDisposedException)
                {
                    return null;
                }

                switch (errorCode)
                {
                    case SocketError.Success:
                        break;

                    case SocketError.WouldBlock:
                    case SocketError.TimedOut:
                    {
                        return null;
                    }
                    default:
                        if (IsDisconnecting == false)
                            throw new Exception($"Failed to receive packet. Error code is {errorCode}.");
                        return null;
                }

                // cipher

                ReceiveCount += recv;
            }

            // 나머지 read
            int packetLength = BitConverter.ToUInt16(RecvBuffer, 0);
            while (ReceiveCount != packetLength)
            {
                int recv;
                try
                {
                    recv = copiedSocket.Receive(RecvBuffer, ReceiveCount, packetLength - ReceiveCount, SocketFlags.None,
                        out errorCode);
                }
                catch (ObjectDisposedException)
                {
                    return null;
                }

                switch (errorCode)
                {
                    case SocketError.Success:
                        break;

                    case SocketError.WouldBlock:
                    case SocketError.TimedOut:
                    {
                        return null;
                    }
                    default:
                        if (IsDisconnecting == false)
                            throw new Exception($"Failed to receive packet. Error code is {errorCode}.");
                        return null;
                }

                // cipher

                ReceiveCount += recv;
            }

            ReceiveCount = 0;
            BinaryReader.BaseStream.Seek(0, SeekOrigin.Begin);
            
            BinaryReader.ReadUInt16();
            UInt16 packetId = BinaryReader.ReadUInt16();

            var packetEnum = (Protocol.ProtocolEnum)packetId;

            var packetType = ProtocolHelper.GetPacketType(packetEnum);
            if (packetType == null)
            {
                throw new KeyNotFoundException($"Invalid Packet Id: {packetId}");
            }

            return new C_MOVE();
        }
    }
}
