#include "pch.h"
#include <IoContext.h>
#include <ServerService.h>
#include <ThreadManager.h>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

int main()
{
	spdlog::info("init spdlog");
	
	IoContext ioContext;
	ServerService serverService{ ioContext, EndPoint{"127.0.0.1", 712} };
	serverService.Start();

	std::thread thread([](IoContext* context)
	{
		while(true)
		{
			context->Run();			
		}
	}, &ioContext);

	thread.join();

	return 0;
}
