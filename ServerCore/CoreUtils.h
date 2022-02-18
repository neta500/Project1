#pragma once
#include <numeric>
#include "spdlog/spdlog.h"

namespace util
{
	void Crash(const std::string& str);
}

template<class T, class U>
struct std::hash<std::pair<T, U>>
{
	std::size_t operator()(const std::pair<T, U>& val) const
	{
		return CombineHash(val.first, val.second);
	}
};

inline std::size_t CombineHashImpl(const std::initializer_list<std::size_t> hashes)
{
	return std::accumulate(hashes.begin(), hashes.end(), (std::size_t)0,
		[](std::size_t seed, std::size_t value)
		{
			return seed ^ (value + 0x9e3779b9 + (seed << 6) + (seed >> 2));
		});
}

template<class T>
std::size_t ComputeHash(const T& val)
{
	std::hash<T> h;

	return h(val);
}

template<class... T>
std::size_t CombineHash(const T& ... vals)
{
	return CombineHashImpl({ ComputeHash(vals)... });
}

