#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <stringapiset.h>

class FileUtils
{
public:
	static std::vector<std::byte> ReadFile(const wchar_t* path)
	{
		std::vector<std::byte> ret;
		const std::filesystem::path filePath{ path };

		const auto fileSize = std::filesystem::file_size(filePath);
		ret.resize(fileSize);

		std::basic_ifstream<std::byte> inputStream{ filePath };
		inputStream.read(&ret[0], static_cast<std::streamsize>(fileSize));

		return ret;
	}

	static std::wstring ToWStr(const std::string& str)
	{
		const int length = static_cast<int>(str.size());
		std::wstring ret;
		if (length == 0)
		{
			return ret;
		}

		const int retLen = ::MultiByteToWideChar(CP_UTF8, 0, &str[0], length, nullptr, 0);
		ret.resize(retLen);
		::MultiByteToWideChar(CP_UTF8, 0, &str[0], length, &ret[0], retLen);

		return ret;
	}
};