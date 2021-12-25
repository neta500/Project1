#pragma once
#include "TestClass.h"

class EmplaceBackTestClass
{
public:
	void TestFunction()
	{
		std::vector<Cat> catVec;

		// ���� : Cat�� int�� �����ڷ� ���� �� �ִ�.
		Cat cat1{11};
		//catVec.push_back(cat1); // copy 1
		//catVec.push_back(std::move(cat1)); // move 1
		//catVec.push_back(Cat{}); // move 1
		catVec.push_back(5); // move 1

		//catVec.emplace_back(cat1); // copy 1
		//catVec.emplace_back(std::move(cat1)); // move 1
		//catVec.emplace_back(Cat{}); // move 1
		catVec.emplace_back(10); // zero overhead

		// ������ emplace_back�� ������ ��� �����ڿ� ���� ȣ���ϱ� ������ �ǵ����� ���� �۾��� �Ͼ �� �ִ�.
		std::vector<std::unique_ptr<Cat>> catPtrVec;		

		//catPtrVec.push_back(std::addressof(cat1));
		//catPtrVec.emplace_back(std::addressof(cat1)); // cat1�� ���� �����̱� ������ unique_ptr�� �Ҹ�Ǹ鼭 ���� ��û �� heap runtime error�� �߻��Ѵ�.

		auto catPtr = std::make_unique<Cat>(13);
		catPtrVec.emplace_back(catPtr.release()); // �������� unique_ptr ��� �� ����
	}
};