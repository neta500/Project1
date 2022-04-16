:: 경로 설정
pushd %~dp0

:: protobuf 파일 생성
protoc --proto_path=./ --cpp_out=./ --csharp_out=./ ./Protocol.proto
IF ERRORLEVEL 1 PAUSE

:: 생성된 protobuf 파일 복사
XCOPY /Y Protocol.pb.h "../GameServer"
XCOPY /Y Protocol.pb.cc "../GameServer"
XCOPY /Y Protocol.cs "../DummyClient/Protocol"