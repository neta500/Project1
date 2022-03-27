#pragma once
#include <minwinbase.h>

enum class IoType
{
	Send,
	Recv,
	Accept,
	Connect,
	Disconnect
};

class IocpOperation : public OVERLAPPED
{
public:
	IocpOperation(const IoType ioType);
};