#pragma once

class IoContext
{
public:
	IoContext();
	~IoContext() = default;
	
	void Run();
	bool RegisterAcceptor(const HANDLE acceptorHandle);

	void TestPushJob();
	
private:
	HANDLE mIocpHandle = nullptr;
};