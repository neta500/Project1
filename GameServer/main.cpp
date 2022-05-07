#include "pch.h"
#include <IoContext.h>
#include <ServerService.h>
#include <ThreadManager.h>
#include <boost/asio.hpp>
#include <DBConnectionPool.h>
#include "ClientSession.h"

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

	// test query
	{
		auto query = L" \
		DROP TABLE IF EXISTS [dbo].[Gold];	\
		CREATE TABLE [dbo].[Gold]	\
		(	\
			[id] INT NOT NULL PRIMARY KEY IDENTITY, \
			[gold] INT NULL	\
		);";

		auto connection = GDBConnectionPool->Pop();
		if (false == connection->Execute(query))
		{
			spdlog::critical("db query failed");
		}
		GDBConnectionPool->Push(connection);
	}

	{
		for (int i = 0; i < 3; ++i)
		{
			auto connection = GDBConnectionPool->Pop();
			connection->UnBind();

			int gold = 100;
			SQLLEN len = 0;
			connection->BindParam(1, SQL_C_LONG, SQL_INTEGER, sizeof(gold), &gold, &len);

			auto query = L"INSERT INTO [dbo].[Gold]([gold]) VALUES(?)";
			connection->Execute(query);
			GDBConnectionPool->Push(connection);
		}
	}

	{
		auto connection = GDBConnectionPool->Pop();
		connection->UnBind();

		int gold = 100;
		SQLLEN len = 0;
		connection->BindParam(1, SQL_C_LONG, SQL_INTEGER, sizeof(gold), &gold, &len);
		auto query = L"SELECT id, gold FROM [dbo].[Gold] WHERE gold = (?)";

		int outId = 0;
		SQLLEN outIdLen = 0;
		connection->BindCol(1, SQL_C_LONG, sizeof(outId), &outId, &outIdLen);

		int outGold = 0;
		SQLLEN outGoldLen = 0;
		connection->BindCol(2, SQL_C_LONG, sizeof(outGold), &outGold, &outGoldLen);
		connection->Execute(query);

		while (connection->Fetch())
		{
			spdlog::info("[SELECT] id: {}, gold: {}", outId, outGold);
		}
		GDBConnectionPool->Push(connection);
	}

	std::this_thread::sleep_for(std::chrono::seconds(10000));

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
