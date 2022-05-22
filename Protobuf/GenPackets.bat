:: 경로 설정
pushd %~dp0

:: protobuf 파일 생성 (proto파일이 변화가 없으면 안해도될듯?)
protoc --proto_path=./ --cpp_out=./ --csharp_out=./ ./Protocol.proto

GenPackets.exe --path=./Protocol.proto

IF ERRORLEVEL 1 PAUSE

:: 생성된 protobuf 파일 복사:XCOPY /Y Protocol.pb.h "../GameServer"
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