#include "pch.h"
#include <IoContext.h>
#include <ServerService.h>
#include <ThreadManager.h>
#include <boost/asio.hpp>

#include "ClientSession.h"

using namespace boost::asio::ip;

int main()
{
	spdlog::info("init spdlog");

	ClientPacketHandler::Init();
		
	IoContext ioContext;
	ServerService serverService{ ioContext, EndPoint{"127.0.0.1", 712} };
	serverService.SetSession(std::make_shared<ClientSession>(ioContext));
	serverService.Start();

	std::thread thread([](IoContext* context)
	{
		while(true)
		{
			//context->TestPushJob();
			context->Run();			
		}
	}, &ioContext);
		
	thread.join();
	
	return 0;
}
