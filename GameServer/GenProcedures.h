// this file is auto generated file. do not edit!

#pragma once
#include "DBBind.h"

namespace SP
{
	
    class InsertGold : public DBBind<3,0>
    {
    public:
    	InsertGold(DBConnection& conn) : DBBind(conn, L"{CALL dbo.InsertGold(?,?,?)}") {}
    	void In_Gold(int& v) { BindParam(0, v); }
    	void In_Gold(int&& v) { _gold = std::move(v); BindParam(0, _gold); }
    	template<int N> void In_Name(wchar_t(&v)[N]) { BindParam(1, v); }
    	template<int N> void In_Name(const wchar_t(&v)[N]) { BindParam(1, v); }
    	void In_Name(wchar_t* v, int count) { BindParam(1, v, count); }
    	void In_Name(const wchar_t* v, int count) { BindParam(1, v, count); }
    	void In_CreateDate(TIMESTAMP_STRUCT& v) { BindParam(2, v); }
    	void In_CreateDate(TIMESTAMP_STRUCT&& v) { _createDate = std::move(v); BindParam(2, _createDate); }

    private:
    	int _gold = {};
    	TIMESTAMP_STRUCT _createDate = {};
    };

    class SelectGold : public DBBind<1,4>
    {
    public:
    	SelectGold(DBConnection& conn) : DBBind(conn, L"{CALL dbo.SelectGold(?)}") {}
    	void In_Gold(int& v) { BindParam(0, v); }
    	void In_Gold(int&& v) { _gold = std::move(v); BindParam(0, _gold); }
    	void Out_Id(int& v) { BindCol(0, v); }
    	void Out_Gold(int& v) { BindCol(1, v); }
    	template<int N> void Out_Name(wchar_t(&v)[N]) { BindCol(2, v); }
    	void Out_CreateDate(TIMESTAMP_STRUCT& v) { BindCol(3, v); }

    private:
    	int _gold = {};
    };


     
};