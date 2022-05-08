#pragma once
#include <sql.h>
#include <sqlext.h>
#include <iostream>

class DBConnection
{
	enum
	{
		WVARCHAR_MAX = 4000,
		BINARY_MAX = 8000
	};

public:
	bool Connect(SQLHENV henv, const wchar_t* connectionString)
	{
		if (::SQLAllocHandle(SQL_HANDLE_DBC, henv, &mConnection) != SQL_SUCCESS)
		{
			return false;
		}

		wchar_t stringBuffer[MAX_PATH] = { 0 };
		::wcscpy_s(stringBuffer, connectionString);

		wchar_t resultString[MAX_PATH] = { 0 };
		SQLSMALLINT resultStringLen = 0;

		SQLRETURN ret = ::SQLDriverConnectW(
			mConnection,
			nullptr,
			stringBuffer,
			_countof(stringBuffer),
			resultString,
			_countof(resultString),
			&resultStringLen,
			SQL_DRIVER_NOPROMPT
		);

		if (::SQLAllocHandle(SQL_HANDLE_STMT, mConnection, &mStatement) != SQL_SUCCESS)
		{
			return false;
		}

		return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);		
	}

	void Clear()
	{
		if (mConnection)
		{
			::SQLFreeHandle(SQL_HANDLE_DBC, mConnection);
		}

		if (mStatement)
		{
			::SQLFreeHandle(SQL_HANDLE_DBC, mStatement);
		}
	}

	bool Execute(const wchar_t* query)
	{
		SQLRETURN ret = ::SQLExecDirectW(mStatement, (SQLWCHAR*)query, SQL_NTSL);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			return true;
		}

		HandleError(ret);
		return false;
	}

	bool Fetch()
	{
		switch (const auto ret = ::SQLFetch(mStatement))
		{
		case SQL_SUCCESS:
		case SQL_SUCCESS_WITH_INFO:
			return true;
		case SQL_NO_DATA:
			return false;
		case SQL_ERROR:
			HandleError(ret);
			return false;
		default:
			return true;
		}
	}
	int GetRowCount()
	{
		SQLLEN count = 0;
		auto ret = ::SQLRowCount(mStatement, &count);

		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			return static_cast<int>(count);
		}

		return -1;
	}

	void UnBind()
	{
		::SQLFreeStmt(mStatement, SQL_UNBIND);
		::SQLFreeStmt(mStatement, SQL_RESET_PARAMS);
		::SQLFreeStmt(mStatement, SQL_CLOSE);		
	}

public:
	bool BindParam(int paramIndex, bool* value, SQLLEN* index)
	{
		return BindCol(paramIndex, SQL_C_TINYINT, static_cast<int>(sizeof(bool)), value, index);
	}
	bool BindParam(int paramIndex, float* value, SQLLEN* index)
	{
		return BindParam(paramIndex, SQL_C_FLOAT, SQL_REAL, 0, value, index);
	}
	bool BindParam(int paramIndex, double* value, SQLLEN* index)
	{
		return BindParam(paramIndex, SQL_C_DOUBLE, SQL_DOUBLE, 0, value, index);
	}
	bool BindParam(int paramIndex, signed char* value, SQLLEN* index)
	{
		return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, static_cast<int>(sizeof(signed char)), value, index);
	}
	bool BindParam(int paramIndex, short* value, SQLLEN* index)
	{
		return BindParam(paramIndex, SQL_C_SHORT, SQL_SMALLINT, static_cast<int>(sizeof(short)), value, index);
	}
	bool BindParam(int paramIndex, int* value, SQLLEN* index)
	{
		return BindParam(paramIndex, SQL_C_LONG, SQL_INTEGER, static_cast<int>(sizeof(int)), value, index);
	}
	bool BindParam(int paramIndex, long long* value, SQLLEN* index)
	{
		return BindParam(paramIndex, SQL_C_SBIGINT, SQL_BIGINT, static_cast<int>(sizeof(long long)), value, index);
	}
	bool BindParam(int paramIndex, TIMESTAMP_STRUCT* value, SQLLEN* index)
	{
		return BindParam(paramIndex, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, static_cast<int>(sizeof(TIMESTAMP_STRUCT)), value, index);
	}
	bool BindParam(int paramIndex, const wchar_t* str, SQLLEN* index)
	{
		SQLULEN size = (::wcslen(str) + 1) * 2;
		*index = SQL_NTSL;

		if (size > WVARCHAR_MAX)
			return BindParam(paramIndex, SQL_C_WCHAR, SQL_WLONGVARCHAR, size, (SQLPOINTER)str, index);
		else
			return BindParam(paramIndex, SQL_C_WCHAR, SQL_WVARCHAR, size, (SQLPOINTER)str, index);
	}
	bool BindParam(int paramIndex, const std::byte* bin, int size, SQLLEN* index)
	{
		if (bin == nullptr)
		{
			*index = SQL_NULL_DATA;
			size = 1;
		}
		else
			*index = size;

		if (size > BINARY_MAX)
			return BindParam(paramIndex, SQL_C_BINARY, SQL_LONGVARBINARY, size, (BYTE*)bin, index);
		else
			return BindParam(paramIndex, SQL_C_BINARY, SQL_BINARY, size, (BYTE*)bin, index);
	}

	bool BindCol(int columnIndex, bool* value, SQLLEN* index)
	{
		return BindCol(columnIndex, SQL_C_TINYINT, static_cast<int>(sizeof(bool)), value, index);
	}
	bool BindCol(int columnIndex, float* value, SQLLEN* index)
	{
		return BindCol(columnIndex, SQL_C_TINYINT, static_cast<int>(sizeof(bool)), value, index);
	}
	bool BindCol(int columnIndex, double* value, SQLLEN* index)
	{
		return BindCol(columnIndex, SQL_C_DOUBLE, static_cast<int>(sizeof(double)), value, index);
	}
	bool BindCol(int columnIndex, signed char* value, SQLLEN* index)
	{
		return BindCol(columnIndex, SQL_C_TINYINT, static_cast<int>(sizeof(signed char)), value, index);
	}
	bool BindCol(int columnIndex, short* value, SQLLEN* index)
	{
		return BindCol(columnIndex, SQL_C_SHORT, static_cast<int>(sizeof(short)), value, index);
	}
	bool BindCol(int columnIndex, int* value, SQLLEN* index)
	{
		return BindCol(columnIndex, SQL_C_LONG, static_cast<int>(sizeof(int)), value, index);
	}
	bool BindCol(int columnIndex, long long* value, SQLLEN* index)
	{
		return BindCol(columnIndex, SQL_C_SBIGINT, static_cast<int>(sizeof(long long)), value, index);
	}
	bool BindCol(int columnIndex, TIMESTAMP_STRUCT* value, SQLLEN* index)
	{
		return BindCol(columnIndex, SQL_C_TYPE_TIMESTAMP, static_cast<int>(sizeof(TIMESTAMP_STRUCT)), value, index);
	}
	bool BindCol(int columnIndex, wchar_t* str, const int size, SQLLEN* index)
	{
		return BindCol(columnIndex, SQL_C_WCHAR, size, str, index);
	}
	bool BindCol(int columnIndex, std::byte* bin, const int size, SQLLEN* index)
	{
		return BindCol(columnIndex, SQL_BINARY, size, bin, index);
	}

private:
	bool BindParam(SQLUSMALLINT paramIndex, SQLSMALLINT cType, SQLSMALLINT sqlType, SQLULEN len, SQLPOINTER ptr, SQLLEN* index)
	{
		auto ret = ::SQLBindParameter(mStatement, paramIndex, SQL_PARAM_INPUT, cType, sqlType, len, 0, ptr, 0, index);
		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			HandleError(ret);
			return false;
		}

		return true;
	}

	bool BindCol(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len, SQLPOINTER value, SQLLEN* index)
	{
		auto ret = ::SQLBindCol(mStatement, columnIndex, cType, value, len, index);
		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			HandleError(ret);
			return false;
		}

		return true;
	}

	void HandleError(SQLRETURN ret)
	{
		if (ret == SQL_SUCCESS)
		{
			return;
		}

		SQLSMALLINT index = 1;
		SQLWCHAR sqlState[MAX_PATH] = { 0 };
		SQLINTEGER nativeErr = 0;
		SQLWCHAR errMsg[MAX_PATH] = { 0 };
		SQLSMALLINT msgLen = 0;
		SQLRETURN errorRet = 0;

		while (true)
		{
			::SQLGetDiagRecW(
				SQL_HANDLE_STMT,
				mStatement,
				index,
				sqlState,
				&nativeErr,
				errMsg,
				_countof(errMsg),
				&msgLen
			);

			if (errorRet == SQL_NO_DATA)
			{
				break;
			}

			if (errorRet != SQL_SUCCESS && errorRet != SQL_SUCCESS_WITH_INFO)
			{
				break;
			}

			std::wcout.imbue(std::locale("kor"));
			std::wcout << errMsg << std::endl;

			index++;

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

private:
	SQLHDBC mConnection = nullptr;
	SQLHSTMT mStatement = nullptr;
};
