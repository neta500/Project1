#include "pch.h"
#include <IoContext.h>
#include <ServerService.h>
#include <ThreadManager.h>
#include <boost/asio.hpp>
#include <DBConnectionPool.h>
#include "ClientSession.h"
#include "DBBind.h"
#include "XmlParser.h"
#include "DBSynchronizer.h"

#include "GenProcedures.h"

using namespace boost::asio::ip;

DBConnectionPool* GDBConnectionPool = nullptr;

int main()
{
	spdlog::info("init spdlog");

	// TODO : Make Database Config
	GDBConnectionPool = new DBConnectionPool();
	const std::wstring dbConnectionString = L"Driver={ODBC Driver 17 for SQL Server};Server=SHSHIN\\SQLEXPRESS;Database=GameDb;Trusted_Connection=Yes;";
	if (false == GDBConnectionPool->Connect(1, dbConnectionString.c_str()))
	{
		spdlog::critical("db connect failed");
	}
	else
	{
		spdlog::info("db connected");
	}	

	auto dbConnection = GDBConnectionPool->Pop();
	DBSynchronizer dbSync(*dbConnection);
	dbSync.Synchronize(L"../Database/GameDatabaseDefinition.xml");

	{
		// TODO : dbConnection을 자동으로 넣어주도록 DBCommand wrapper class 자동생성
		SP::InsertGold dbCommand(*dbConnection);
		dbCommand.In_Gold(999);
		dbCommand.In_Name(L"ASDF");
		dbCommand.In_CreateDate(TIMESTAMP_STRUCT{ 1999,5,15,2 });
		dbCommand.Execute();
	}

	{
		int gold = 0;
		wchar_t name[100]{};
		TIMESTAMP_STRUCT time{};

		SP::SelectGold dbCommand(*dbConnection);
		dbCommand.In_Gold(999);
		dbCommand.Out_Gold(gold);
		dbCommand.Out_Name(name);
		dbCommand.Out_CreateDate(time);

		if (dbCommand.Execute())
		{
			while (dbCommand.Fetch())
			{
				spdlog::info("select gold:{}, name:{}");
			}
		}
	}

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
