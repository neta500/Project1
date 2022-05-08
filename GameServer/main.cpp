#include "pch.h"
#include <IoContext.h>
#include <ServerService.h>
#include <ThreadManager.h>
#include <boost/asio.hpp>
#include <DBConnectionPool.h>
#include "ClientSession.h"
#include "DBBind.h"

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
			[gold] INT NULL,	\
			[name] NVARCHAR(50) NULL, \
			[createDate] DATETIME NULL \
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
			auto query = L"INSERT INTO [dbo].[Gold]([gold], [name], [createDate]) VALUES(?, ?, ?)";

			int gold = 100;
			WCHAR name[100] = L"neta500";
			TIMESTAMP_STRUCT ts = { 2000,1,1 };

			DBBind<3, 0> dbBind(*connection, query);
			dbBind.BindParam(0, gold);
			dbBind.BindParam(1, name);
			dbBind.BindParam(2, ts);

			connection->Execute(query);
			GDBConnectionPool->Push(connection);
		}
	}

	{
		auto connection = GDBConnectionPool->Pop();
		connection->UnBind();

		auto query = L"SELECT id, gold, name, createDate FROM [dbo].[Gold] WHERE gold = (?)";
		DBBind<1, 4> dbBind(*connection, query);

		int gold = 100;
		dbBind.BindParam(0, gold);

		int outId = 0;
		int outGold = 0;
		constexpr auto outNameSize = 50;
		wchar_t outName[outNameSize]{};
		TIMESTAMP_STRUCT outDate = {};

		dbBind.BindCol(0, outId);
		dbBind.BindCol(1, outGold);
		dbBind.BindCol(2, outName);
		dbBind.BindCol(3, outDate);

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
