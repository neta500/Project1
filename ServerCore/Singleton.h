#pragma once

template<class _Ty>
class Singleton
{
public:
	static _Ty& Get()
	{
		static _Ty instance{ token{} };
		return instance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator= (const Singleton&) = delete;

protected:
	struct token {};
	Singleton() {};
};