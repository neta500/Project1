:: ��� ����
pushd %~dp0

:: protobuf ���� ����
protoc --proto_path=./ --cpp_out=./ --csharp_out=./ ./Protocol.proto
IF ERRORLEVEL 1 PAUSE

:: ������ protobuf ���� ����
XCOPY /Y Protocol.pb.h "../GameServer"
XCOPY /Y Protocol.pb.cc "../GameServer"
XCOPY /Y Protocol.cs "../DummyClient/Protocol"