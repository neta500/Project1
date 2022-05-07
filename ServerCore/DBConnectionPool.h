#pragma once
#include "SpinLock.h"
#include "DBConnection.h"
#include <vector>

class DBConnectionPool
{
public:
	bool Connect(const int count, const wchar_t* connectionString)
	{
		WRITE_LOCK;

		if (::SQLAllocHandle(SQL_HANDLE_ENV, nullptr, &mSqlEnv) != SQL_SUCCESS)
		{
			return false;
		}

		if (::SQLSetEnvAttr(mSqlEnv, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0) != SQL_SUCCESS)
		{
			return false;
		}

		for (int i = 0; i < count; ++i)
		{
			auto connection = new DBConnection();
			if (false == connection->Connect(mSqlEnv, connectionString))
			{
				return false;
			}

			mConnections.emplace_back(connection);
		}

		return true;
	}

	void Clear()
	{
		WRITE_LOCK;

		if (mSqlEnv != nullptr)
		{
			::SQLFreeHandle(SQL_HANDLE_ENV, mSqlEnv);
			mSqlEnv = nullptr;
		}

		for (const auto connection : mConnections)
		{
			delete connection;
		}

		mConnections.clear();
	}

	DBConnection* Pop()
	{
		WRITE_LOCK;

		if (mConnections.empty())
		{
			return nullptr;
		}

		DBConnection* connection = mConnections.back();
		mConnections.pop_back();

		return connection;
	}

	void Push(DBConnection* connection)
	{
		WRITE_LOCK;
		mConnections.emplace_back(connection);
	}

private:
	USE_LOCK;
	SQLHENV mSqlEnv = nullptr;
	std::vector<DBConnection*> mConnections{};
};
