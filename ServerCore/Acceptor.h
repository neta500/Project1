#pragma once
#include "EndPoint.h"
#include "IoContext.h"

class ServerService;

class Acceptor
{
public:
	Acceptor(IoContext& ioContext, const EndPoint& endPoint, const ServerService* service);

	void Accept();

private:
	IoContext& mIoContext;
	SOCKET mListenSocket = 0;
	EndPoint mEndPoint;
	const ServerService* mServerService;	
};
