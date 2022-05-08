#pragma once
#include "DBConnection.h"
#include <mutex>
#include <vector>

class DBConnectionPool
{
public:
	bool Connect(const int count, const wchar_t* connectionString)
	{
		std::scoped_lock lock;

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
		std::scoped_lock lock;

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
		std::scoped_lock lock;

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
		std::scoped_lock lock;
		mConnections.emplace_back(connection);
	}

private:
	std::mutex mLock{};
	SQLHENV mSqlEnv = nullptr;
	std::vector<DBConnection*> mConnections{};
};
