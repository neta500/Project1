#pragma once
#include "spdlog/spdlog.h"

class Animal
{
public:
	virtual void Test() = 0;
};

class Cat : public Animal
{
public:
	Cat() { spdlog::info("Cat Constructor"); }
	Cat(const int age) : mAge(age)
	{
		spdlog::info("Cat Constructor(age:{})", age);
	}
	~Cat() { spdlog::info("~Cat Destructor"); }

	Cat(const Cat& other)
		: mAge(other.mAge)
	{
		spdlog::info("Cat Copy Constructor");
	}
	Cat(Cat&& other) noexcept
		: mAge(other.mAge) { spdlog::info("Cat Move Constructor"); }

	virtual void Test() {}

	int mAge = 5;
};

class Dog : public Animal
{
public:
	virtual void Test() {}
	void DogFunc() { spdlog::info("{}", mTest); }

	int mTest = 3;
};


