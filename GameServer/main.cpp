#include "pch.h"
#include <IoContext.h>
#include <ServerService.h>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

int main()
{
	spdlog::info("init spdlog");
	
	IoContext ioContext;
	ServerService serverService{ ioContext, EndPoint{"127.0.0.1", 712} };

	return 0;
}
