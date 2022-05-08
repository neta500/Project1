#pragma once
#include <rapidxml/rapidxml.hpp>
#include <memory>
#include <string>
#include "FileUtils.h"

using namespace rapidxml;

using XmlNodeType = xml_node<wchar_t>;
using XmlDocumentType = xml_document<wchar_t>;
using XmlAttributeType = xml_attribute<wchar_t>;

class XmlNode
{
	_locale_t kr = _create_locale(LC_NUMERIC, "kor");

public:
	explicit XmlNode(XmlNodeType* node = nullptr) : mNode(node) {}

	bool IsValid() { return mNode != nullptr; }

	// TODO : defaultValue함수와 default를 사용하지 않는 함수 구분(필수입력attr)
	// TODO : wcsicmp -> wcsieq
	// TODO : Pair, List 함수 제작
	bool GetBoolAttr(const wchar_t* key, bool defaultValue = false) const
	{
		if (const auto attr = mNode->first_attribute(key))
		{
			return ::_wcsicmp(attr->value(), L"true") == 0;
		}
		
		return defaultValue;
	}

	int GetIntAttr(const wchar_t* key, int defaultValue = 0) const
	{
		if (const auto attr = mNode->first_attribute(key))
		{
			return ::_wtoi(attr->value());
		}

		return defaultValue;
	}

	float GetFloatAttr(const wchar_t* key, float defaultValue = 0.f) const
	{
		if (const auto attr = mNode->first_attribute(key))
		{
			return static_cast<float>(::_wtof(attr->value()));
		}

		return defaultValue;
	}

	double GetDoubleAttr(const wchar_t* key, double defaultValue = 0) const
	{
		if (const auto attr = mNode->first_attribute(key))
		{
			return ::_wtof_l(attr->value(), kr);
		}

		return defaultValue;
	}

	__int64 GetInt64Attr(const wchar_t* key, __int64 defaultValue = 0) const
	{
		if (const auto attr = mNode->first_attribute(key))
		{
			return ::_wtoi64(attr->value());
		}

		return defaultValue;
	}

	const wchar_t* GetStringAttr(const wchar_t* key, const wchar_t* defaultValue = L"") const
	{
		if (const auto attr = mNode->first_attribute(key))
		{
			return attr->value();
		}

		return defaultValue;
	}

	bool GetBoolValue(bool defaultValue = false) const
	{
		if (const auto val = mNode->value())
		{
			return ::_wcsicmp(val, L"true") == 0;
		}

		return defaultValue;
	}

	int GetIntValue(int defaultValue = 0) const
	{
		if (const auto val = mNode->value())
		{
			return ::_wtoi(val);
		}

		return defaultValue;
	}

	float GetFloatValue(float defaultValue = 0.f) const
	{
		if (const auto val = mNode->value())
		{
			return static_cast<float>(::_wtof(val));
		}

		return defaultValue;
	}

	double GetDoubleValue(double defaultValue = 0) const
	{
		if (const auto val = mNode->value())
		{
			return ::_wtof_l(val, kr);
		}

		return defaultValue;
	}

	__int64 GetInt64Value(__int64 defaultValue = 0) const
	{
		if (const auto val = mNode->value())
		{
			return ::_wtoi64(val);
		}

		return defaultValue;
	}

	const wchar_t* GetStringValue(const wchar_t* defaultValue = L"") const
	{
		if (const auto val = mNode->first_node()->value())
		{
			return val;
		}

		return defaultValue;
	}

	XmlNode FindChild(const wchar_t* key) const
	{
		return XmlNode{ mNode->first_node(key) };
	}

	std::vector<XmlNode> FindChildren(const wchar_t* key) const
	{
		std::vector<XmlNode> nodes{};
		auto node = mNode->first_node(key);
		while (node)
		{
			nodes.emplace_back(node);
			node = node->next_sibling(key);
		}

		return nodes;
	}

private:
	XmlNodeType* mNode = nullptr;
};

class XmlParser
{
public:
	bool ParseFromFile(const wchar_t* path, XmlNode& root)
	{
		const std::vector<std::byte> byteVector = FileUtils::ReadFile(path);
		mData = FileUtils::ToWStr(std::string(reinterpret_cast<const char*>(&byteVector[0]), byteVector.size()));

		if (mData.empty())
		{
			return false;
		}

		mDocument = std::make_shared<XmlDocumentType>();
		mDocument->parse<0>(&mData[0]);
		root = XmlNode(mDocument->first_node());
		return true;
	}

private:
	std::shared_ptr<XmlDocumentType> mDocument = nullptr;
	std::wstring mData{};
};