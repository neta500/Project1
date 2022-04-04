#pragma once
#include "spdlog/spdlog.h"

class Animal
{
public:
	virtual ~Animal() = default;
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
	~Cat() override { spdlog::info("~Cat Destructor"); }

	Cat(const Cat& other)
		: mAge(other.mAge)
	{
		spdlog::info("Cat Copy Constructor");
	}
	Cat(Cat&& other) noexcept
		: mAge(other.mAge) { spdlog::info("Cat Move Constructor"); }

	Cat& operator=(const Cat&)
	{
		spdlog::info("Cat copy assignment");
		return *this;
	}

	Cat& operator=(Cat&&) noexcept
	{
		spdlog::info("Cat move assignment");
		return *this;
	}

	virtual void Test()
	{
		spdlog::info("cattt");
	}

	int mAge = 5;
};

class Dog : public Animal
{
public:
	virtual void Test()
	{
		spdlog::info("doggg");
	}
	void DogFunc() { spdlog::info("{}", mTest); }

	int mTest = 3;
};

class Test
{
public:
	int Get() const
	{
		std::scoped_lock lock(mMutex);
		spdlog::info("Get, mInt: {}", mInt);
		return mInt;
	}

	void Plus()
	{
		std::scoped_lock lock(mMutex);
		mInt++;
		spdlog::info("Plus, mInt: {}", mInt);
	}

	void Set(const int expected)
	{
		std::scoped_lock lock(mMutex);
		mInt = expected + 1;
		spdlog::info("Set, mInt: {}", mInt);
	}

	mutable std::mutex mMutex;
	int mInt = 0;
	std::shared_ptr<Cat> mCat;
};