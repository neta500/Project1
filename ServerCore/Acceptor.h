#pragma once
#include "EndPoint.h"
#include "IoContext.h"

class ServerService;
class IocpOperation;

class Acceptor
{
public:
	Acceptor(IoContext& ioContext, const EndPoint& endPoint, const ServerService* service);

	void Accept();


	IoContext& mIoContext;
	SOCKET mListenSocket = 0;
	EndPoint mEndPoint;
	const ServerService* mServerService;

	std::shared_ptr<IocpOperation> mAcceptOperation = nullptr;
};
