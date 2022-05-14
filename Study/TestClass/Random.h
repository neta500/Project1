#pragma once
#include <random>

class Random
{
public:
	static int GetRandomInt(const int min, const int max)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> uni(1, 100);
		return uni(rng);
	}
};
