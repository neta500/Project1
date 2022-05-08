#pragma once
#include <set>
#include <map>

#include "DBBind.h"
#include "DBConnection.h"
#include "XmlDb.h"
#include "XmlParser.h"

#include <spdlog/spdlog.h>

// TODO : identity를 도중에 추가할 경우 업데이트 안되는 문제 수정 (drop 이후 add identity 필요)
// 위의 경우 라이브에서는 불가능한 일이고, 개발중에 이런경우가 있을순있겠음.

class DBSynchronizer
{
	enum
	{
		PROCEDURE_MAX_LEN = 10000
	};

	// TODO : 싱글쿼리 업데이트
	enum UpdateStep : unsigned char
	{
		DropIndex = 0,
		AlterColumn = 1,
		AddColumn = 2,
		CreateTable = 3,
		DefaultConstraint = 4,
		CreateIndex = 5,
		DropColumn = 6,
		DropTable = 7,
		StoredProcecure = 8,
		Max
	};

	enum ColumnFlag : unsigned char
	{
		Type = 1 << 0,
		Nullable = 1 << 1,
		Identity = 1 << 2,
		Default = 1 << 3,
		Length = 1 << 4,
	};

	inline const static WCHAR* QTablesAndColumns =
		L"	SELECT c.object_id, t.name AS tableName, c.name AS columnName, c.column_id, c.user_type_id, c.max_length,"
		"		c.is_nullable, c.is_identity, CAST(ic.seed_value AS BIGINT) AS seedValue, CAST(ic.increment_value AS BIGINT) AS incValue,"
		"		c.default_object_id, dc.definition as defaultDefinition, dc.name as defaultConstraintName"
		"	FROM sys.columns AS c"
		"	JOIN sys.tables AS t"
		"		ON c.object_id = t.object_id"
		"	LEFT JOIN sys.default_constraints AS dc"
		"		ON c.default_object_id = dc.object_id"
		"	LEFT JOIN sys.identity_columns AS ic"
		"		ON c.object_id = ic.object_id AND c.column_id = ic.column_id"
		"	WHERE t.type = 'U'"
		"	ORDER BY object_id ASC, column_id ASC;";

	class GetDBTables : public DBBind<0, 13>
	{
	public:
		explicit GetDBTables(DBConnection& conn) : DBBind(conn, QTablesAndColumns) {}

		void Out_ObjectId(OUT int& value) { BindCol(0, value); }
		template<int N> void Out_TableName(OUT WCHAR(&value)[N]) { BindCol(1, value); }
		template<int N> void Out_ColumnName(OUT WCHAR(&value)[N]) { BindCol(2, value); }
		void Out_ColumnId(OUT int& value) { BindCol(3, value); }
		void Out_UserType(OUT int& value) { BindCol(4, value); }
		void Out_MaxLength(OUT int& value) { BindCol(5, value); }
		void Out_IsNullable(OUT bool& value) { BindCol(6, value); }
		void Out_IsIdentity(OUT bool& value) { BindCol(7, value); }
		void Out_SeedValue(OUT __int64& value) { BindCol(8, value); }
		void Out_IncrementValue(OUT __int64& value) { BindCol(9, value); }
		void Out_DefaultObjectId(OUT int& value) { BindCol(10, value); }
		template<int N> void Out_DefaultDefinition(OUT WCHAR(&value)[N]) { BindCol(11, value); }
		template<int N> void Out_DefaultConstraintName(OUT WCHAR(&value)[N]) { BindCol(12, value); }
	};

	inline const static WCHAR* QIndexes =
		L"	SELECT i.object_id, i.name as indexName, i.index_id, i.type, i.is_primary_key,"
		"		i.is_unique_constraint, ic.column_id, COL_NAME(ic.object_id, ic.column_id) as columnName"
		"	FROM sys.indexes AS i"
		"	JOIN sys.index_columns AS ic"
		"		ON i.object_id = ic.object_id AND i.index_id = ic.index_id"
		"	WHERE i.type > 0 AND i.object_id IN(SELECT object_id FROM sys.tables WHERE type = 'U')"
		"	ORDER BY i.object_id ASC, i.index_id ASC;";

	class GetDBIndexes : public DBBind<0, 8>
	{
	public:
		GetDBIndexes(DBConnection& conn) : DBBind(conn, QIndexes) {}

		void Out_ObjectId(OUT int& value) { BindCol(0, value); }
		template<int N> void Out_IndexName(OUT WCHAR(&value)[N]) { BindCol(1, value); }
		void Out_IndexId(OUT int& value) { BindCol(2, value); }
		void Out_IndexType(OUT int& value) { BindCol(3, value); }
		void Out_IsPrimaryKey(OUT bool& value) { BindCol(4, value); }
		void Out_IsUniqueConstraint(OUT bool& value) { BindCol(5, value); }
		void Out_ColumnId(OUT int& value) { BindCol(6, value); }
		template<int N> void Out_ColumnName(OUT WCHAR(&value)[N]) { BindCol(7, value); }
	};

	inline const static WCHAR* QStoredProcedures =
		L"	SELECT name, OBJECT_DEFINITION(object_id) AS body FROM sys.procedures;";

	class GetDBStoredProcedures : public DBBind<0, 2>
	{
	public:
		GetDBStoredProcedures(DBConnection& conn) : DBBind(conn, QStoredProcedures) {}

		template<int N> void Out_Name(OUT WCHAR(&value)[N]) { BindCol(0, value); }
		void Out_Body(OUT WCHAR* value, int len) { BindCol(1, value, len); }
	};

public:
	explicit DBSynchronizer(DBConnection& conn) : _dbConn(conn) { }
	~DBSynchronizer() = default;

	bool Synchronize(const wchar_t* path)
	{
		ParseXmlDB(path);

		GatherDBTables();
		GatherDBIndexes();
		GatherDBStoredProcedures();

		CompareDBModel();
		ExecuteUpdateQueries();

		return true;
	}

private:
	void ParseXmlDB(const wchar_t* path)
	{
		XmlNode root;
		XmlParser parser;
		//ASSERT_CRASH(parser.ParseFromFile(path, OUT root));
		if (false == parser.ParseFromFile(path, root))
		{
			// throw;
		}

		std::vector<XmlNode> tables = root.FindChildren(L"Table");
		for (XmlNode& table : tables)
		{
			auto t = std::make_shared<XmlDb::Table>();
			t->mName = table.GetStringAttr(L"name");

			std::vector<XmlNode> columns = table.FindChildren(L"Column");
			for (XmlNode& column : columns)
			{
				auto c = std::make_shared<XmlDb::Column>();
				c->mName = column.GetStringAttr(L"name");
				c->mTypeText = column.GetStringAttr(L"type");
				c->mType = XmlDb::Helpers::ToDataType(c->mTypeText.c_str(), OUT c->mMaxLength);

				//ASSERT_CRASH(c->_type != DBModel::DataType::None);
				if (c->mType == XmlDb::DataType::None)
				{
					// throw
				}

				c->mNullable = !column.GetBoolAttr(L"notnull", false);

				const WCHAR* identityStr = column.GetStringAttr(L"identity");
				if (::wcslen(identityStr) > 0)
				{
					std::wregex pt(L"(\\d+),(\\d+)");
					std::wcmatch match;
					if (false == std::regex_match(identityStr, OUT match, pt))
					{
						//ASSERT_CRASH(std::regex_match(identityStr, OUT match, pt));
						// throw
					}
					c->mIdentity = true;
					c->mSeedValue = _wtoi(match[1].str().c_str());
					c->mIncrementValue = _wtoi(match[2].str().c_str());
				}

				c->mDefault = column.GetStringAttr(L"default");
				t->mColumns.push_back(c);
			}

			std::vector<XmlNode> indexes = table.FindChildren(L"Index");
			for (XmlNode& index : indexes)
			{
				auto i = std::make_shared<XmlDb::Index>();
				const WCHAR* typeStr = index.GetStringAttr(L"type");
				if (::_wcsicmp(typeStr, L"clustered") == 0)
					i->mType = XmlDb::IndexType::Clustered;
				else if (::_wcsicmp(typeStr, L"nonclustered") == 0)
					i->mType = XmlDb::IndexType::NonClustered;
				else
					// CRASH("Invalid Index Type");
					// throw

				i->mPrimaryKey = index.FindChild(L"PrimaryKey").IsValid();
				i->mUniqueConstraint = index.FindChild(L"UniqueKey").IsValid();

				std::vector<XmlNode> indexColumns = index.FindChildren(L"Column");
				for (XmlNode& column : indexColumns)
				{
					const WCHAR* nameStr = column.GetStringAttr(L"name");
					auto c = t->FindColumn(nameStr);

					if (c == nullptr)
					{
						//ASSERT_CRASH(c != nullptr);
						// throw
					}

					i->mColumns.push_back(c);
				}

				t->mIndexes.push_back(i);
			}

			_xmlTables.push_back(t);
		}

		std::vector<XmlNode> procedures = root.FindChildren(L"Procedure");
		for (XmlNode& procedure : procedures)
		{
			auto p = std::make_shared<XmlDb::Procedure>();
			p->mName = procedure.GetStringAttr(L"name");
			p->mBody = procedure.FindChild(L"Body").GetStringValue();

			std::vector<XmlNode> params = procedure.FindChildren(L"Param");
			for (XmlNode& paramNode : params)
			{
				XmlDb::Param param;
				param.mName = paramNode.GetStringAttr(L"name");
				param.mType = paramNode.GetStringAttr(L"type");
				p->mParameters.push_back(param);
			}

			_xmlProcedures.push_back(p);
		}

		std::vector<XmlNode> removedTables = root.FindChildren(L"RemovedTable");
		for (XmlNode& removedTable : removedTables)
		{
			_xmlRemovedTables.insert(removedTable.GetStringAttr(L"name"));
		}
	}

	bool GatherDBTables()
	{
		int objectId;
		WCHAR tableName[101] = { 0 };
		WCHAR columnName[101] = { 0 };
		int columnId;
		int userTypeId;
		int maxLength;
		bool isNullable;
		bool isIdentity;
		__int64 seedValue;
		__int64 incValue;
		int defaultObjectId;
		WCHAR defaultDefinition[101] = { 0 };
		WCHAR defaultConstraintName[101] = { 0 };

		GetDBTables getDBTables(_dbConn);
		getDBTables.Out_ObjectId(OUT objectId);
		getDBTables.Out_TableName(OUT tableName);
		getDBTables.Out_ColumnName(OUT columnName);
		getDBTables.Out_ColumnId(OUT columnId);
		getDBTables.Out_UserType(OUT userTypeId);
		getDBTables.Out_MaxLength(OUT maxLength);
		getDBTables.Out_IsNullable(OUT isNullable);
		getDBTables.Out_IsIdentity(OUT isIdentity);
		getDBTables.Out_SeedValue(OUT seedValue);
		getDBTables.Out_IncrementValue(OUT incValue);
		getDBTables.Out_DefaultObjectId(OUT defaultObjectId);
		getDBTables.Out_DefaultDefinition(OUT defaultDefinition);
		getDBTables.Out_DefaultConstraintName(OUT defaultConstraintName);

		if (getDBTables.Execute() == false)
			return false;

		while (getDBTables.Fetch())
		{
			std::shared_ptr<XmlDb::Table> table;

			if (auto findTable = std::ranges::find_if(_dbTables,
				[=](const auto& t)
				{
					return t->mObjectId == objectId;
				}); findTable == _dbTables.end())
			{
				table = std::make_shared<XmlDb::Table>();
				table->mObjectId = objectId;
				table->mName = tableName;
				_dbTables.push_back(table);
			}
			else
			{
				table = *findTable;
			}

			auto column = std::make_shared<XmlDb::Column>();

			{
				column->mName = columnName;
				column->mColumnId = columnId;
				column->mType = static_cast<XmlDb::DataType>(userTypeId);
				column->mTypeText = XmlDb::Helpers::ToString(column->mType);
				column->mMaxLength = (column->mType == XmlDb::DataType::Nvarchar ? maxLength / 2 : maxLength);
				column->mNullable = isNullable;
				column->mIdentity = isIdentity;
				column->mSeedValue = (isIdentity ? seedValue : 0);
				column->mIncrementValue = (isIdentity ? incValue : 0);

				if (defaultObjectId > 0)
				{
					column->mDefault = defaultDefinition;
					unsigned __int64 p = column->mDefault.find_first_not_of('(');
					column->mDefault = column->mDefault.substr(p, column->mDefault.size() - p * 2);
					column->mDefaultConstraintName = defaultConstraintName;
				}
			}

			table->mColumns.push_back(column);
		}

		return true;
	}

	bool GatherDBIndexes()
	{
		int objectId;
		WCHAR indexName[101] = { 0 };
		int indexId;
		int indexType;
		bool isPrimaryKey;
		bool isUniqueConstraint;
		int columnId;
		WCHAR columnName[101] = { 0 };

		GetDBIndexes getDBIndexes(_dbConn);
		getDBIndexes.Out_ObjectId(OUT objectId);
		getDBIndexes.Out_IndexName(OUT indexName);
		getDBIndexes.Out_IndexId(OUT indexId);
		getDBIndexes.Out_IndexType(OUT indexType);
		getDBIndexes.Out_IsPrimaryKey(OUT isPrimaryKey);
		getDBIndexes.Out_IsUniqueConstraint(OUT isUniqueConstraint);
		getDBIndexes.Out_ColumnId(OUT columnId);
		getDBIndexes.Out_ColumnName(OUT columnName);

		if (getDBIndexes.Execute() == false)
		{
			return false;			
		}

		while (getDBIndexes.Fetch())
		{
			auto findTable = std::ranges::find_if(_dbTables, [=](const auto& table) { return table->mObjectId == objectId; });

			if (findTable == _dbTables.end())
			{
				//ASSERT_CRASH(findTable != _dbTables.end());
				// throw
			}

			std::vector<std::shared_ptr<XmlDb::Index>>& indexes = (*findTable)->mIndexes;
			auto findIndex = std::ranges::find_if(indexes, [indexId](auto& index) { return index->mIndexId == indexId; });
			if (findIndex == indexes.end())
			{
				auto index = std::make_shared<XmlDb::Index>();
				{
					index->mName = indexName;
					index->mIndexId = indexId;
					index->mType = static_cast<XmlDb::IndexType>(indexType);
					index->mPrimaryKey = isPrimaryKey;
					index->mUniqueConstraint = isUniqueConstraint;
				}
				indexes.push_back(index);
				findIndex = indexes.end() - 1;
			}

			// 인덱스가 걸린 column 찾아서 매핑해준다.
			auto& columns = (*findTable)->mColumns;
			auto findColumn = std::ranges::find_if(columns, [columnId](auto& column) { return column->mColumnId == columnId; });

			if (findColumn == columns.end())
			{
				// throw
				//ASSERT_CRASH(findColumn != columns.end());
			}

			(*findIndex)->mColumns.push_back(*findColumn);
		}

		return true;
	}

	bool GatherDBStoredProcedures()
	{
		WCHAR name[101] = { 0 };
		std::vector<WCHAR> body(PROCEDURE_MAX_LEN);

		GetDBStoredProcedures getDBStoredProcedures(_dbConn);
		getDBStoredProcedures.Out_Name(OUT name);
		getDBStoredProcedures.Out_Body(OUT & body[0], PROCEDURE_MAX_LEN);

		if (getDBStoredProcedures.Execute() == false)
			return false;

		while (getDBStoredProcedures.Fetch())
		{
			auto proc = std::make_shared<XmlDb::Procedure>();
			{
				proc->mName = name;
				proc->mFullBody = std::wstring(body.begin(), std::ranges::find(body, 0));
			}
			_dbProcedures.push_back(proc);
		}

		return true;
	}

	void CompareDBModel()
	{
		// 업데이트 목록 초기화.
		_dependentIndexes.clear();
		for (std::vector<std::wstring>& queries : _updateQueries)
		{
			queries.clear();			
		}

		// XML에 있는 목록을 우선 갖고 온다.
		std::map<std::wstring, std::shared_ptr<XmlDb::Table>> xmlTableMap;
		for (const auto& xmlTable : _xmlTables)
		{
			xmlTableMap[xmlTable->mName] = xmlTable;			
		}

		// DB에 실존하는 테이블들을 돌면서 XML에 정의된 테이블들과 비교한다.
		for (const auto& dbTable : _dbTables)
		{
			auto findTable = xmlTableMap.find(dbTable->mName);
			if (findTable != xmlTableMap.end())
			{
				auto& xmlTable = findTable->second;
				CompareTables(dbTable, xmlTable);
				xmlTableMap.erase(findTable);
			}
			else
			{
				if (_xmlRemovedTables.contains(dbTable->mName))
				{
					//GConsoleLogger->WriteStdOut(Color::YELLOW, L"Removing Table : [dbo].[%s]\n", dbTable->_name.c_str());
					_updateQueries[UpdateStep::DropTable].push_back(XmlDb::Helpers::Format(L"DROP TABLE [dbo].[%s]", dbTable->mName.c_str()));
				}
			}
		}

		// 맵에서 제거되지 않은 XML 테이블 정의는 새로 추가.
		for (auto& mapIt : xmlTableMap)
		{
			const auto& xmlTable = mapIt.second;

			std::wstring columnsStr;
			const int size = static_cast<int>(xmlTable->mColumns.size());
			for (int i = 0; i < size; i++)
			{
				if (i != 0)
					columnsStr += L",";
				columnsStr += L"\n\t";
				columnsStr += xmlTable->mColumns[i]->CreateText();
			}

			//GConsoleLogger->WriteStdOut(Color::YELLOW, L"Creating Table : [dbo].[%s]\n", xmlTable->_name.c_str());
			_updateQueries[UpdateStep::CreateTable].push_back(XmlDb::Helpers::Format(L"CREATE TABLE [dbo].[%s] (%s)", xmlTable->mName.c_str(), columnsStr.c_str()));

			for (const auto& xmlColumn : xmlTable->mColumns)
			{
				if (xmlColumn->mDefault.empty())
					continue;

				_updateQueries[UpdateStep::DefaultConstraint].push_back(XmlDb::Helpers::Format(L"ALTER TABLE [dbo].[%s] ADD CONSTRAINT [%s] DEFAULT (%s) FOR [%s]",
					xmlTable->mName.c_str(),
					XmlDb::Helpers::Format(L"DF_%s_%s", xmlTable->mName.c_str(), xmlColumn->mName.c_str()).c_str(),
					xmlColumn->mDefault.c_str(),
					xmlColumn->mName.c_str()));
			}

			for (const auto& xmlIndex : xmlTable->mIndexes)
			{
				//GConsoleLogger->WriteStdOut(Color::YELLOW, L"Creating Index : [%s] %s %s [%s]\n", xmlTable->_name.c_str(), xmlIndex->GetKeyText().c_str(), xmlIndex->GetTypeText().c_str(), xmlIndex->GetUniqueName().c_str());
				if (xmlIndex->mPrimaryKey || xmlIndex->mUniqueConstraint)
				{
					_updateQueries[UpdateStep::CreateIndex].push_back(XmlDb::Helpers::Format(
						L"ALTER TABLE [dbo].[%s] ADD CONSTRAINT [%s] %s %s (%s)",
						xmlTable->mName.c_str(),
						xmlIndex->CreateName(xmlTable->mName).c_str(),
						xmlIndex->GetKeyText().c_str(),
						xmlIndex->GetTypeText().c_str(),
						xmlIndex->CreateColumnsText().c_str()));
				}
				else
				{
					_updateQueries[UpdateStep::CreateIndex].push_back(XmlDb::Helpers::Format(
						L"CREATE %s INDEX [%s] ON [dbo].[%s] (%s)",
						xmlIndex->GetTypeText().c_str(),
						xmlIndex->CreateName(xmlTable->mName).c_str(),
						xmlTable->mName.c_str(),
						xmlIndex->CreateColumnsText().c_str()));
				}
			}
		}

		CompareStoredProcedures();
	}
	void CompareTables(std::shared_ptr<XmlDb::Table> dbTable, std::shared_ptr<XmlDb::Table> xmlTable)
	{
		// XML에 있는 컬럼 목록을 갖고 온다.
		std::map<std::wstring, std::shared_ptr<XmlDb::Column>> xmlColumnMap;
		for (auto& xmlColumn : xmlTable->mColumns)
			xmlColumnMap[xmlColumn->mName] = xmlColumn;

		// DB에 실존하는 테이블 컬럼들을 돌면서 XML에 정의된 컬럼들과 비교한다.
		for (auto& dbColumn : dbTable->mColumns)
		{
			auto findColumn = xmlColumnMap.find(dbColumn->mName);
			if (findColumn != xmlColumnMap.end())
			{
				auto& xmlColumn = findColumn->second;
				CompareColumns(dbTable, dbColumn, xmlColumn);
				xmlColumnMap.erase(findColumn);
			}
			else
			{
				//GConsoleLogger->WriteStdOut(Color::YELLOW, L"Dropping Column : [%s].[%s]\n", dbTable->_name.c_str(), dbColumn->_name.c_str());
				if (dbColumn->mDefaultConstraintName.empty() == false)
					_updateQueries[UpdateStep::DropColumn].push_back(XmlDb::Helpers::Format(L"ALTER TABLE [dbo].[%s] DROP CONSTRAINT [%s]", dbTable->mName.c_str(), dbColumn->mDefaultConstraintName.c_str()));

				_updateQueries[UpdateStep::DropColumn].push_back(XmlDb::Helpers::Format(L"ALTER TABLE [dbo].[%s] DROP COLUMN [%s]", dbTable->mName.c_str(), dbColumn->mName.c_str()));
			}
		}

		// 맵에서 제거되지 않은 XML 컬럼 정의는 새로 추가.
		for (auto& mapIt : xmlColumnMap)
		{
			auto& xmlColumn = mapIt.second;
			auto newColumn = *xmlColumn;
			newColumn.mNullable = true;

			//GConsoleLogger->WriteStdOut(Color::YELLOW, L"Adding Column : [%s].[%s]\n", dbTable->_name.c_str(), xmlColumn->_name.c_str());
			_updateQueries[UpdateStep::AddColumn].push_back(XmlDb::Helpers::Format(L"ALTER TABLE [dbo].[%s] ADD %s %s",
				dbTable->mName.c_str(), xmlColumn->mName.c_str(), xmlColumn->mTypeText.c_str()));

			if (xmlColumn->mNullable == false && xmlColumn->mDefault.empty() == false)
			{
				_updateQueries[UpdateStep::AddColumn].push_back(XmlDb::Helpers::Format(L"SET NOCOUNT ON; UPDATE [dbo].[%s] SET [%s] = %s WHERE [%s] IS NULL",
					dbTable->mName.c_str(), xmlColumn->mName.c_str(), xmlColumn->mDefault.c_str(), xmlColumn->mName.c_str()));
			}

			if (xmlColumn->mNullable == false)
			{
				_updateQueries[UpdateStep::AddColumn].push_back(XmlDb::Helpers::Format(L"ALTER TABLE [dbo].[%s] ALTER COLUMN %s",
					dbTable->mName.c_str(), xmlColumn->CreateText().c_str()));
			}

			if (xmlColumn->mDefault.empty() == false)
			{
				_updateQueries[UpdateStep::AddColumn].push_back(XmlDb::Helpers::Format(L"ALTER TABLE [dbo].[%s] ADD CONSTRAINT [DF_%s_%s] DEFAULT (%s) FOR [%s]",
					dbTable->mName.c_str(), dbTable->mName.c_str(), xmlColumn->mName.c_str(), xmlColumn->mDefault.c_str(), xmlColumn->mName.c_str()));
			}
		}

		// XML에 있는 인덱스 목록을 갖고 온다.
		std::map<std::wstring, std::shared_ptr<XmlDb::Index>> xmlIndexMap;
		for (auto& xmlIndex : xmlTable->mIndexes)
			xmlIndexMap[xmlIndex->GetUniqueName()] = xmlIndex;

		// DB에 실존하는 테이블 인덱스들을 돌면서 XML에 정의된 인덱스들과 비교한다.
		for (auto& dbIndex : dbTable->mIndexes)
		{
			auto findIndex = xmlIndexMap.find(dbIndex->GetUniqueName());
			if (findIndex != xmlIndexMap.end() && _dependentIndexes.find(dbIndex->GetUniqueName()) == _dependentIndexes.end())
			{
				xmlIndexMap.erase(findIndex);
			}
			else
			{
				//GConsoleLogger->WriteStdOut(Color::YELLOW, L"Dropping Index : [%s] [%s] %s %s\n", dbTable->_name.c_str(), dbIndex->_name.c_str(), dbIndex->GetKeyText().c_str(), dbIndex->GetTypeText().c_str());
				if (dbIndex->mPrimaryKey || dbIndex->mUniqueConstraint)
					_updateQueries[UpdateStep::DropIndex].push_back(XmlDb::Helpers::Format(L"ALTER TABLE [dbo].[%s] DROP CONSTRAINT [%s]", dbTable->mName.c_str(), dbIndex->mName.c_str()));
				else
					_updateQueries[UpdateStep::DropIndex].push_back(XmlDb::Helpers::Format(L"DROP INDEX [%s] ON [dbo].[%s]", dbIndex->mName.c_str(), dbTable->mName.c_str()));
			}
		}

		// 맵에서 제거되지 않은 XML 인덱스 정의는 새로 추가.
		for (auto& mapIt : xmlIndexMap)
		{
			auto xmlIndex = mapIt.second;
			//GConsoleLogger->WriteStdOut(Color::YELLOW, L"Creating Index : [%s] %s %s [%s]\n", dbTable->_name.c_str(), xmlIndex->GetKeyText().c_str(), xmlIndex->GetTypeText().c_str(), xmlIndex->GetUniqueName().c_str());
			if (xmlIndex->mPrimaryKey || xmlIndex->mUniqueConstraint)
			{
				_updateQueries[UpdateStep::CreateIndex].push_back(XmlDb::Helpers::Format(L"ALTER TABLE [dbo].[%s] ADD CONSTRAINT [%s] %s %s (%s)",
					dbTable->mName.c_str(), xmlIndex->CreateName(dbTable->mName).c_str(), xmlIndex->GetKeyText().c_str(), xmlIndex->GetTypeText().c_str(), xmlIndex->CreateColumnsText().c_str()));
			}
			else
			{
				_updateQueries[UpdateStep::CreateIndex].push_back(XmlDb::Helpers::Format(L"CREATE %s INDEX [%s] ON [dbo].[%s] (%s)",
					xmlIndex->GetTypeText().c_str(), xmlIndex->CreateName(dbTable->mName).c_str(), dbTable->mName.c_str(), xmlIndex->CreateColumnsText().c_str()));
			}
		}
	}

	void CompareColumns(std::shared_ptr<XmlDb::Table> dbTable, std::shared_ptr<XmlDb::Column> dbColumn, std::shared_ptr<XmlDb::Column> xmlColumn)
	{
		unsigned char flag = 0;

		if (dbColumn->mType != xmlColumn->mType)
			flag |= ColumnFlag::Type;
		if (dbColumn->mMaxLength != xmlColumn->mMaxLength && xmlColumn->mMaxLength > 0)
			flag |= ColumnFlag::Length;
		if (dbColumn->mNullable != xmlColumn->mNullable)
			flag |= ColumnFlag::Nullable;
		if (dbColumn->mIdentity != xmlColumn->mIdentity || (dbColumn->mIdentity && dbColumn->mIncrementValue != xmlColumn->mIncrementValue))
			flag |= ColumnFlag::Identity;
		if (dbColumn->mDefault != xmlColumn->mDefault)
			flag |= ColumnFlag::Default;

		if (flag)
		{
			//GConsoleLogger->WriteStdOut(Color::YELLOW, L"Updating Column [%s] : (%s) -> (%s)\n", dbTable->_name.c_str(), dbColumn->CreateText().c_str(), xmlColumn->CreateText().c_str());
		}

		// 연관된 인덱스가 있으면 나중에 삭제하기 위해 기록한다.
		if (flag & (ColumnFlag::Type | ColumnFlag::Length | ColumnFlag::Nullable))
		{
			for (auto& dbIndex : dbTable->mIndexes)
				if (dbIndex->IsDependsOn(dbColumn->mName))
					_dependentIndexes.insert(dbIndex->GetUniqueName());

			flag |= ColumnFlag::Default;
		}

		if (flag & ColumnFlag::Default)
		{
			if (dbColumn->mDefaultConstraintName.empty() == false)
			{
				_updateQueries[UpdateStep::AlterColumn].push_back(XmlDb::Helpers::Format(
					L"ALTER TABLE [dbo].[%s] DROP CONSTRAINT [%s]",
					dbTable->mName.c_str(),
					dbColumn->mDefaultConstraintName.c_str()));
			}
		}

		auto& newColumn = *dbColumn;
		newColumn.mDefault = L"";
		newColumn.mType = xmlColumn->mType;
		newColumn.mMaxLength = xmlColumn->mMaxLength;
		newColumn.mTypeText = xmlColumn->mTypeText;
		newColumn.mSeedValue = xmlColumn->mSeedValue;
		newColumn.mIdentity = xmlColumn->mIdentity;
		newColumn.mIncrementValue = xmlColumn->mIncrementValue;

		if (flag & (ColumnFlag::Type | ColumnFlag::Length | ColumnFlag::Identity))
		{
			_updateQueries[UpdateStep::AlterColumn].push_back(XmlDb::Helpers::Format(
				L"ALTER TABLE [dbo].[%s] ALTER COLUMN %s",
				dbTable->mName.c_str(),
				newColumn.CreateText().c_str()));
		}

		newColumn.mNullable = xmlColumn->mNullable;
		if (flag & ColumnFlag::Nullable)
		{
			if (xmlColumn->mDefault.empty() == false)
			{
				_updateQueries[UpdateStep::AlterColumn].push_back(XmlDb::Helpers::Format(
					L"SET NOCOUNT ON; UPDATE [dbo].[%s] SET [%s] = %s WHERE [%s] IS NULL",
					dbTable->mName.c_str(),
					xmlColumn->mName.c_str(),
					xmlColumn->mName.c_str(),
					xmlColumn->mName.c_str()));
			}

			_updateQueries[UpdateStep::AlterColumn].push_back(XmlDb::Helpers::Format(
				L"ALTER TABLE [dbo].[%s] ALTER COLUMN %s",
				dbTable->mName.c_str(),
				newColumn.CreateText().c_str()));
		}

		if (flag & ColumnFlag::Default)
		{
			if (dbColumn->mDefaultConstraintName.empty() == false)
			{
				_updateQueries[UpdateStep::AlterColumn].push_back(XmlDb::Helpers::Format(
					L"ALTER TABLE [dbo].[%s] ADD CONSTRAINT [%s] DEFAULT (%s) FOR [%s]",
					dbTable->mName.c_str(),
					XmlDb::Helpers::Format(L"DF_%s_%s", dbTable->mName.c_str(), dbColumn->mName.c_str()).c_str(),
					dbColumn->mDefault.c_str(), dbColumn->mName.c_str()));
			}
		}
	}

	void CompareStoredProcedures()
	{
		// XML에 있는 프로시저 목록을 갖고 온다.
		std::map<std::wstring, std::shared_ptr<XmlDb::Procedure>> xmlProceduresMap;
		for (auto& xmlProcedure : _xmlProcedures)
			xmlProceduresMap[xmlProcedure->mName] = xmlProcedure;

		// DB에 실존하는 테이블 프로시저들을 돌면서 XML에 정의된 프로시저들과 비교한다.
		for (auto& dbProcedure : _dbProcedures)
		{
			auto findProcedure = xmlProceduresMap.find(dbProcedure->mName);
			if (findProcedure != xmlProceduresMap.end())
			{
				auto xmlProcedure = findProcedure->second;
				auto xmlBody = xmlProcedure->GenerateCreateQuery();
				if (XmlDb::Helpers::RemoveWhiteSpace(dbProcedure->mFullBody) != XmlDb::Helpers::RemoveWhiteSpace(xmlBody))
				{
					//GConsoleLogger->WriteStdOut(Color::YELLOW, L"Updating Procedure : %s\n", dbProcedure->_name.c_str());
					_updateQueries[UpdateStep::StoredProcecure].push_back(xmlProcedure->GenerateAlterQuery());
				}
				xmlProceduresMap.erase(findProcedure);
			}
		}

		// 맵에서 제거되지 않은 XML 프로시저 정의는 새로 추가.
		for (auto& mapIt : xmlProceduresMap)
		{
			//GConsoleLogger->WriteStdOut(Color::YELLOW, L"Updating Procedure : %s\n", mapIt.first.c_str());
			_updateQueries[UpdateStep::StoredProcecure].push_back(mapIt.second->GenerateCreateQuery());
		}
	}

	void ExecuteUpdateQueries()
	{
		for (auto& _updateQuerie : _updateQueries)
		{
			for (auto& query : _updateQuerie)
			{
				_dbConn.UnBind();
				if (_dbConn.Execute(query.c_str()))
				{
					//throw
				}
			}
		}
	}

private:
	DBConnection& _dbConn;

	std::vector<std::shared_ptr<XmlDb::Table>> _xmlTables{};
	std::vector<std::shared_ptr<XmlDb::Procedure>> _xmlProcedures{};
	std::set<std::wstring> _xmlRemovedTables{};

	std::vector<std::shared_ptr<XmlDb::Table>> _dbTables{};
	std::vector<std::shared_ptr<XmlDb::Procedure>> _dbProcedures{};

	std::set<std::wstring> _dependentIndexes{};
	std::vector<std::wstring> _updateQueries[UpdateStep::Max]{};
};
