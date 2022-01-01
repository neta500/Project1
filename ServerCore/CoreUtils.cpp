#include "pch.h"
#include "CoreUtils.h"

void util::Crash(const std::string& str)
{
	spdlog::critical(str);
	std::abort();
}
