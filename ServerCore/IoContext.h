#pragma once

class IoContext
{
public:
	IoContext();
	~IoContext() = default;
	
	void Run();
	
private:
	HANDLE mIocpHandle = nullptr;
};