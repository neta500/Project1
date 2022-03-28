#pragma once

class IoContext
{
public:
	IoContext();
	~IoContext() = default;
	
	void Run();
	bool RegisterAcceptor(const HANDLE acceptorHandle);
	
private:
	HANDLE mIocpHandle = nullptr;
};