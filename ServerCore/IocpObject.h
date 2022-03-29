#pragma once
#include <winsock.h>

class IocpOperation;

class IocpObject
{
public:
	virtual HANDLE GetHandle() = 0;
	virtual void HandleIocp(IocpOperation* operation, const int bytes) = 0;
};