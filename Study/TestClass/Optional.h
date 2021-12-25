#pragma once
#include "TestClass.h"

class OptionalTestClass
{
public:
	OptionalTestClass() = default;
	~OptionalTestClass() = default;

public:
	// 0 Copy
	const std::optional<std::reference_wrapper<const Cat>> GetCatOptionalRef(const int age) const
	{
		if (mCat.mAge == age)
		{
			return std::ref(mCat);
		}

		return std::nullopt;
	}

	// 1 Copy
	std::optional<Cat> GetCatOptional(const int age) const
	{
		if (mCat.mAge == age)
		{
			return mCat;
		}

		return std::nullopt;
	}

	// 1 Copy
	Cat GetCatValue() const
	{
		return mCat;
	}

	// 0 Copy
	const Cat& GetCatRef() const
	{ 
		return mCat;
	}	

	Cat mCat{5};
};
