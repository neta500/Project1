#pragma once
#include <vector>

// STL Container�� erase-remove idiom�� �����ϸ� ȿ�������� ������ �ذ��� �� �ִ�.
// �׳� �����̳ʸ� ó������ ������ ��ȸ�ϸ鼭 0�� ã�Ƽ� �����ϰ�, �ڿ� ���̸� ������..

class Solution
{
public:
	void moveZeroes(std::vector<int>& nums)
	{
		int lastNonZeroIndex = 0;
		for (int curr = 0; curr < nums.size(); ++curr)
		{
			// 0�� �ƴ� ���Ҹ� ã�Ƽ�, �տ������� �������� ä���ִ´�.
			if (nums[curr] != 0)
			{				
				nums[lastNonZeroIndex] = nums[curr];
				lastNonZeroIndex++;
			}
		}

		// �޺κ� 0���� �о��ش�.
		for (int i = lastNonZeroIndex; i < nums.size(); ++i)
		{
			nums[i] = 0;
		}
	}
};