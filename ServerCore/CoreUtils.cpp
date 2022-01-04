#include "pch.h"
#include "CoreUtils.h"

void util::Crash(const std::string& str)
{
	spdlog::critical(str);
	int* crashForMe = nullptr;
	__analysis_assume(crashForMe != nullptr);
	*crashForMe = 0x15998255;
}
