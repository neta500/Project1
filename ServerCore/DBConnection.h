#pragma once
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <xstring>
#include "spdlog/spdlog.h"
#pragma warning(disable:4244)

class DBConnection
{
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

			const std::wstring wstr(errMsg);
			const std::string str(wstr.cbegin(), wstr.cend());
			spdlog::error("SQL Error: {}", str);
		}
	}

private:
	SQLHDBC mConnection = nullptr;
	SQLHSTMT mStatement = nullptr;
};