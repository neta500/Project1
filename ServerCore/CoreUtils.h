#pragma once
#include "spdlog/spdlog.h"

namespace util
{
	void Crash(const std::string& str);
}

template <class T> using OptionalRef = std::optional<std::reference_wrapper<T>>;