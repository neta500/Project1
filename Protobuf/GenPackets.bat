:: ��� ����
pushd %~dp0

:: protobuf ���� ���� (proto������ ��ȭ�� ������ ���ص��ɵ�?)
protoc --proto_path=./ --cpp_out=./ --csharp_out=./ ./Protocol.proto

GenPackets.exe --path=./Protocol.proto

IF ERRORLEVEL 1 PAUSE

:: ������ protobuf ���� ����:XCOPY /Y Protocol.pb.h "../GameServer"
XCOPY /Y Protocol.pb.cc "../GameServer"
XCOPY /Y Protocol.cs "../DummyClient/Protocol"
XCOPY /Y ClientPacketHandler.h "../GameServer"
XCOPY /Y PDL.h "../GameServer"
XCOPY /Y PDL_DummyClient.cs "../DummyClient/Protocol"

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h
DEL /Q /F *.cs

PAUSE