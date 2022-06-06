using System.Net;
using System.Net.Sockets;
using Google.Protobuf;

namespace DummyClient
{
    internal class SocketContext
    {
        public bool Connected => Socket.Connected;
        private volatile Socket Socket;
        private readonly Bot Client;

        private readonly RecvBuffer RecvBuffer = new(65535);
        private readonly SocketAsyncEventArgs RecvArgs = new();

        public Action<Google.Protobuf.IMessage> Callback;

        public SocketContext(Bot owner)
        {
            Client = owner;
        }

        private void RegisterRecv()
        {
            if (Connected == false)
            {
                return;
            }

            RecvBuffer.Clean();
            var segment = RecvBuffer.WriteSegment;
            RecvArgs.SetBuffer(segment.Array, segment.Offset, segment.Count);

            try
            {
                var pending = Socket.ReceiveAsync(RecvArgs);
                if (pending == false)
                {
                    RecvCompleted(null, RecvArgs);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"RegisterRecv failed: {ex}");
            }
        }

        private void RecvCompleted(object sender, SocketAsyncEventArgs args)
        {
            if (args.BytesTransferred > 0 && args.SocketError == SocketError.Success)
            {
                try
                {
                    if (RecvBuffer.OnWrite(args.BytesTransferred) == false)
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
                        return;
                    }

                    RegisterRecv();
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

        public void Connect(string addr, int port)
        {
            IPAddress address = Dns.GetHostAddresses(addr)[0];
            IPEndPoint endPoint = new IPEndPoint(address, port);

            Socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            Socket.NoDelay = true;

            var args = new SocketAsyncEventArgs();
            args.Completed += ConnectCompleted;
            args.RemoteEndPoint = endPoint;
            args.UserToken = Socket;

            var pending = Socket.ConnectAsync(args);
            if (pending == false)
            {
                ConnectCompleted(null, args);
            }
        }

        void ConnectCompleted(object sender, SocketAsyncEventArgs args)
        {
            if (args.SocketError == SocketError.Success)
            {
                RecvArgs.Completed += RecvCompleted;
                RegisterRecv();
            }
            else
            {
                Console.WriteLine($"Connect failed : {args.SocketError}");
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
            Console.WriteLine($"Disconnected");
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

                var packetId = (ushort)(Protocol.ProtocolEnum)Enum.Parse(typeof(Protocol.ProtocolEnum), packetEnumStr);
                var size = (ushort)packet.CalculateSize();
                byte[] sendBuffer = new byte[size + 4];
                Array.Copy(BitConverter.GetBytes(size + 4), 0, sendBuffer, 0, sizeof(ushort));
                Array.Copy(BitConverter.GetBytes(packetId), 0, sendBuffer, 2, sizeof(ushort));
                Array.Copy(packet.ToByteArray(), 0, sendBuffer, 4, size);
                
                SocketError errorCode;

                try
                {
                    copiedSocket.Send(sendBuffer, 0, sendBuffer.Length, SocketFlags.None, out errorCode);
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
    }
}
