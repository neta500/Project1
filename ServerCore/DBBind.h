#pragma once
#include "DBConnection.h"

template<int ParamCount, int ColumnCount>
class DBBind
{
	template<int C>
	struct FullBits { enum { value = (1 << (C - 1)) | FullBits<C - 1>::value }; };
	template<>
	struct FullBits<1> { enum { value = 1 }; };
	template<>
	struct FullBits<0> { enum { value = 0 }; };

public:
	DBBind(DBConnection& dbConnection, const WCHAR* query)
		: mDBConnection(dbConnection), mQuery(query)
	{
		dbConnection.UnBind();
	}

	bool Validate()
	{
		return mParamFlag == FullBits<ParamCount>::value && mColumnFlag == FullBits<ColumnCount>::value;
	}

	bool Execute()
	{
		return mDBConnection.Execute(mQuery);
	}

	bool Fetch()
	{
		return mDBConnection.Fetch();
	}

public:
	template<typename T>
	void BindParam(int index, T& value)
	{
		mDBConnection.BindParam(index + 1, &value, &mParamIndex[index]);
		mParamFlag |= 1LL << index;
	}
	
	void BindParam(int index, const WCHAR* value)
	{
		mDBConnection.BindParam(index + 1, value, &mParamIndex[index]);
		mParamFlag |= 1LL << index;
	}

	template<typename T, int N>
	void BindParam(int index, T(&value)[N])
	{
		mDBConnection.BindParam(index + 1, reinterpret_cast<const std::byte*>(value), sizeof(T) * N, &mParamIndex[index]);
		mParamFlag |= 1LL << index;
	}

	template<typename T>
	void BindParam(int index, T* value, int N)
	{
		mDBConnection.BindParam(index + 1, reinterpret_cast<const std::byte*>(value), sizeof(T) * N, &mParamIndex[index]);
		mParamFlag |= 1LL << index;
	}

	template<typename T>
	void BindCol(int index, T& value)
	{
		mDBConnection.BindCol(index + 1, &value, &mColumnIndex[index]);
		mColumnFlag |= 1LL << index;
	}

	template<int N>
	void BindCol(int index, WCHAR(&value)[N])
	{
		mDBConnection.BindCol(index + 1, value, N - 1, &mColumnIndex[index]);
		mColumnFlag |= 1LL << index;
	}

	void BindCol(int index, WCHAR* value, int len)
	{
		mDBConnection.BindCol(index + 1, value, len - 1, &mColumnIndex[index]);
		mColumnFlag |= 1LL << index;
	}

	template<typename T, int N>
	void BindCol(int index, T(&value)[N])
	{
		mDBConnection.BindCol(index + 1, value, sizeof(T) * N, &mColumnIndex[index]);
		mColumnFlag |= 1LL << index;
	}

protected:
	DBConnection& mDBConnection;
	const WCHAR* mQuery{};
	SQLLEN mParamIndex[ParamCount > 0 ? ParamCount : 1] = {};
	SQLLEN mColumnIndex[ColumnCount > 0 ? ColumnCount : 1] = {};

	// param 개수를 잘 넣었는지 체크하는 비트 플래그
	__int64 mParamFlag = 0;
	__int64 mColumnFlag = 0;
};