#pragma once
#include <regex>
#include <string>
#include <cstdarg>

namespace XmlDb
{
	// For SQL Server
	enum class DataType
	{
		None = 0,
		Tinyint = 48,
		Smallint = 52,
		Int = 56,
		Real = 59,
		DateTime = 61,
		Float = 62,
		Bit = 104,
		Numeric = 108,
		Bigint = 127,
		VarBinary = 165,
		Varchar = 167,
		Binary = 173,
		Nvarchar = 231,
	};

	class Helpers
	{
	public:
		static std::wstring Format(const wchar_t* format, ...)
		{
			constexpr int bufSize = 4096;
			wchar_t buf[bufSize];
			va_list ap;
			va_start(ap, format);
			::vswprintf_s(buf, bufSize, format, ap);
			return std::wstring{ buf };
		}

		static std::wstring ToString(const DataType dataType)
		{
			switch (dataType)
			{
			case DataType::None:		return L"None";
			case DataType::Tinyint:		return L"Tinyint";
			case DataType::Smallint:	return L"Smallint";
			case DataType::Int:			return L"Int";
			case DataType::Real:		return L"Real";
			case DataType::DateTime:	return L"DateTime";
			case DataType::Float:		return L"Float";
			case DataType::Bit:			return L"Bit";
			case DataType::Numeric:		return L"Numeric";
			case DataType::Bigint:		return L"Bigint";
			case DataType::VarBinary:	return L"VarBinary";
			case DataType::Varchar:		return L"Varchar";
			case DataType::Binary:		return L"Binary";
			case DataType::Nvarchar:	return L"Nvarchar";
			}

			return L"None";
		}

		static DataType ToDataType(const wchar_t* str, int& maxLen)
		{
			const std::wregex reg(L"([a-z]+)(\\((max|\\d+)\\))?");
			std::wcmatch ret;

			if (std::regex_match(str, ret, reg) == false)
			{
				return DataType::None;
			}

			if (ret[3].matched)
			{
				maxLen = ::_wcsicmp(ret[3].str().c_str(), L"max") == 0 ? -1 : _wtoi(ret[3].str().c_str());
			}
			else
			{
				maxLen = 0;
			}

			if (::_wcsicmp(ret[1].str().c_str(), L"Tinyint") == 0) return DataType::Tinyint;
			if (::_wcsicmp(ret[1].str().c_str(), L"Smallint") == 0) return DataType::Smallint;
			if (::_wcsicmp(ret[1].str().c_str(), L"Int") == 0) return DataType::Int;
			if (::_wcsicmp(ret[1].str().c_str(), L"Real") == 0) return DataType::Real;
			if (::_wcsicmp(ret[1].str().c_str(), L"DateTime") == 0) return DataType::DateTime;
			if (::_wcsicmp(ret[1].str().c_str(), L"Float") == 0) return DataType::Float;
			if (::_wcsicmp(ret[1].str().c_str(), L"Bit") == 0) return DataType::Bit;
			if (::_wcsicmp(ret[1].str().c_str(), L"Numeric") == 0) return DataType::Numeric;
			if (::_wcsicmp(ret[1].str().c_str(), L"Bigint") == 0) return DataType::Bigint;
			if (::_wcsicmp(ret[1].str().c_str(), L"VarBinary") == 0) return DataType::VarBinary;
			if (::_wcsicmp(ret[1].str().c_str(), L"Varchar") == 0) return DataType::Varchar;
			if (::_wcsicmp(ret[1].str().c_str(), L"Binary") == 0) return DataType::Binary;
			if (::_wcsicmp(ret[1].str().c_str(), L"Nvarchar") == 0) return DataType::Nvarchar;

			return DataType::None;
		}

		static std::wstring RemoveWhiteSpace(const std::wstring& str)
		{
			std::wstring ret = str;
			std::erase_if(ret, [=](const wchar_t ch)
				{
					return ::isspace(ch);
				});
			return ret;
		}
	};

	class Column
	{
	public:
		std::wstring CreateText()
		{
			return XmlDb::Helpers::Format(
				L"[%s] %s %s %s",
				mName.c_str(),
				mTypeText.c_str(),
				mNullable ? L"NULL" : L"NOT NULL",
				mIdentity ? XmlDb::Helpers::Format(L"IDENTITY(%d, %d)", mSeedValue, mIncrementValue).c_str() : L"");
		}

	public:
		std::wstring mName{};
		int mColumnId = 0;
		DataType mType = DataType::None;
		std::wstring mTypeText;
		int mMaxLength = 0;
		bool mNullable = false;
		bool mIdentity = false;
		__int64 mSeedValue = 0;
		__int64 mIncrementValue = 0;

		std::wstring mDefault{};
		std::wstring mDefaultConstraintName{};
	};

	enum class IndexType
	{
		Clustered = 1,
		NonClustered = 2,
	};

	class Index
	{
	public:
		std::wstring GetUniqueName() const
		{
			std::wstring ret;

			ret += mPrimaryKey ? L"PK " : L" ";
			ret += mUniqueConstraint ? L"UK " : L" ";
			ret += (mType == IndexType::Clustered ? L"C " : L"NC ");

			for (const std::shared_ptr<Column>& column : mColumns)
			{
				ret += L"*";
				ret += column->mName;
				ret += L" ";
			}

			return ret;
		}

		std::wstring CreateName(const std::wstring& tableName) const
		{
			std::wstring ret = L"IX_" + tableName;

			for (const std::shared_ptr<Column>& column : mColumns)
			{
				ret += L"_";
				ret += column->mName;
			}

			return ret;
		}

		std::wstring GetTypeText() const
		{
			return mType == IndexType::Clustered ? L"CLUSTERED" : L"NONCLUSTERED";
		}

		std::wstring GetKeyText() const
		{
			if (mPrimaryKey) return L"PRIMARY KEY";
			if (mUniqueConstraint) return L"UNIQUE";
			return L"";
		}

		std::wstring CreateColumnsText() const
		{
			std::wstring ret;

			const int size = static_cast<int>(mColumns.size());
			for (int i = 0; i < size; i++)
			{
				if (i > 0)
					ret += L", ";

				ret += XmlDb::Helpers::Format(L"[%s]", mColumns[i]->mName.c_str());
			}

			return ret;
		}

		bool IsDependsOn(const std::wstring& columnName) const
		{
			const auto findIt = std::ranges::find_if(mColumns,
						 [&](const std::shared_ptr<Column>& column)
						 {
							 return column->mName == columnName;
						 });

			return findIt != mColumns.end();
		}

	public:
		std::wstring mName{};
		int mIndexId = 0;
		IndexType mType = IndexType::NonClustered;
		bool mPrimaryKey = false;
		bool mUniqueConstraint = false;
		std::vector<std::shared_ptr<Column>> mColumns;
	};

	class Table
	{
	public:
		std::shared_ptr<Column> FindColumn(const std::wstring& name) const
		{
			if (const auto findIt = std::ranges::find_if(mColumns,
				[&](const std::shared_ptr<Column>& column)
				{
					return column->mName == name;
				}); findIt != mColumns.end())
			{
				return *findIt;				
			}

			return nullptr;
		}

	public:
		int mObjectId = 0;
		std::wstring mName{};
		std::vector<std::shared_ptr<Column>> mColumns{};
		std::vector<std::shared_ptr<Index>> mIndexes{};
	};

	struct Param
	{
		std::wstring mName{};
		std::wstring mType{};
	};

	class Procedure
	{
	public:
		std::wstring GenerateCreateQuery()
		{
			const wchar_t* query = L"CREATE PROCEDURE [dbo].[%s] %s AS BEGIN %s END";
			std::wstring paramString = GenerateParamString();
			return XmlDb::Helpers::Format(query, mName.c_str(), paramString.c_str(), mBody.c_str());
		}

		std::wstring GenerateAlterQuery()
		{
			const wchar_t* query = L"ALTER PROCEDURE [dbo].[%s] %s AS	BEGIN %s END";

			std::wstring paramString = GenerateParamString();
			return XmlDb::Helpers::Format(query, mName.c_str(), paramString.c_str(), mBody.c_str());
		}

		std::wstring GenerateParamString()
		{
			std::wstring str;

			const int size = static_cast<int>(mParameters.size());
			for (int i = 0; i < size; i++)
			{
				if (i < size - 1)
				{
					str += XmlDb::Helpers::Format(L"\t%s %s,\n", mParameters[i].mName.c_str(), mParameters[i].mType.c_str());
				}
				else
				{
					str += XmlDb::Helpers::Format(L"\t%s %s", mParameters[i].mName.c_str(), mParameters[i].mType.c_str());
				}
			}

			return str;
		}

	public:
		std::wstring mName{};
		std::wstring mFullBody{};
		std::wstring mBody{};
		std::vector<Param> mParameters{};
	};
}