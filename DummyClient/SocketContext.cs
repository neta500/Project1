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

        private volatile bool IsReceiving;
        private volatile bool IsDisconnecting;

        private readonly RecvBuffer RecvBuffer = new RecvBuffer(65535);

        public Action<Google.Protobuf.IMessage> Callback;

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

            IsReceiving = false;
            IsDisconnecting = false;
        }

        // 모든 봇의 Receive 처리 (static queue)
        private static void GlobalReceiveLoop()
        {
            var socketList = new List<SocketContext>();
            var removeCandidate = new List<SocketContext>();

            lock (socketList)
            {
                while (true)
                {
                    Thread.Sleep(TimeSpan.FromMilliseconds(10));

                    while (WaitingQueue.TryDequeue(out var newContext))
                    {
                        socketList.Add(newContext);
                        newContext.IsReceiving = true;
                    }

                    if (socketList.Count == 0)
                    {
                        continue;
                    }

                    foreach (SocketContext context in socketList)
                    {
                        if (context.Socket == null || context.IsDisconnecting)
                        {
                            removeCandidate.Add(context);
                            continue;
                        }
                        
                        context.TryReceivePacket();
                    }

                    foreach (SocketContext context in removeCandidate)
                    {
                        socketList.Remove(context);
                        context.IsReceiving = false;
                    }

                    removeCandidate.Clear();
                }
            }
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
            {
                return;
            }

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
            Callback = callback;
            WaitingQueue.Enqueue(this);

            if (SpinWait.SpinUntil(() => IsReceiving, TimeSpan.FromSeconds(10)) == false)
            {
                throw new Exception("Failed to enqueue to IO thread!");
            }
        }

        public void TryReceivePacket()
        {
            Socket copiedSocket = Socket;
            if (copiedSocket == null)
            {
                return;
            }

            SocketError errorCode;

            int recvBytes;
            try
            {
                var segment = RecvBuffer.WriteSegment;
                recvBytes = copiedSocket.Receive(segment.Array, segment.Offset, segment.Count, SocketFlags.None, out errorCode);
            }
            catch (ObjectDisposedException)
            {
                return;
            }

            switch (errorCode)
            {
                case SocketError.Success:
                    break;

                case SocketError.WouldBlock:
                case SocketError.TimedOut:
                {
                    return;
                }
                default:
                    if (IsDisconnecting == false)
                        throw new Exception($"Failed to receive packet. Error code is {errorCode}.");
                    return;
            }

            if (recvBytes > 0)
            {
                try
                {
                    if (RecvBuffer.OnWrite(recvBytes) == false)
                    {
                        Disconnect();
                        return;
                    }

                    var buffer = RecvBuffer.ReadSegment;

                    int processLen = 0;

                    while (true)
                    {
                        // 헤더 사이즈 체크
                        if (buffer.Count < 2)
                        {
                            break;
                        }

                        ushort dataSize = BitConverter.ToUInt16(buffer.Array!, buffer.Offset);
                        if (buffer.Count < dataSize)
                        {
                            break;
                        }

                        ServerPacketHandler.Instance.OnRecvPacket(this, new ArraySegment<byte>(buffer.Array!, buffer.Offset, dataSize));

                        processLen += dataSize;
                        buffer = new ArraySegment<byte>(buffer.Array!, buffer.Offset + dataSize, buffer.Count - dataSize);
                    }

                    if (processLen == 0 || RecvBuffer.DataSize < processLen)
                    {
                        Disconnect();
                        return;
                    }

                    if (RecvBuffer.OnRead(processLen) == false)
                    {
                        Disconnect();
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                    throw;
                }
            }
            else
            {
                Disconnect();
            }
        }
    }
}
