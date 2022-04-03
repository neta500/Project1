#pragma once

class IoContext
{
public:
	IoContext();
	~IoContext() = default;
	
	void Run();
	bool RegisterIocpHandle(const HANDLE handle) const;

	void TestPushJob();
	
private:
	HANDLE mIocpHandle = nullptr;
};