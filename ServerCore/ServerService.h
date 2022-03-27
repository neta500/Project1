#pragma once
#include "Acceptor.h"
#include "IoContext.h"
#include <memory>

class Session;

class ServerService
{
public:
	ServerService(IoContext& ioContext);


	IoContext& mIoContext;
	Acceptor mAcceptor;
	std::shared_ptr<Session> mSession = nullptr;
};