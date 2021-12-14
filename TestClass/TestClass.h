#pragma once
#include "spdlog/spdlog.h"

class Cat
{
public:
	Cat() { spdlog::info("Cat Constructor"); }
	Cat(const int age) : mAge(age)
	{
		spdlog::info("Cat Constructor(age:{})", age);
	}
	~Cat() { spdlog::info("~Cat Destructor"); }

	Cat(const Cat& other) { spdlog::info("Cat Copy Constructor"); }
	Cat(Cat&& other) noexcept { spdlog::info("Cat Move Constructor"); }

	int mAge = 0;
};