#pragma once
#include <vector>

// STL Container�� erase-remove idiom�� �����ϸ� ȿ�������� ������ �ذ��� �� �ִ�.
// �׳� �����̳ʸ� ó������ ������ ��ȸ�ϸ鼭 0�� ã�Ƽ� �����ϰ�, �ڿ� ���̸� ������..

class Solution
{
public:
	void moveZeroes_1(std::vector<int>& nums)
	{
		for (int lastNonZeroIndex = 0, curr = 0; curr < nums.size(); ++curr)
		{
			if (nums[curr] != 0)
			{
				std::swap(nums[lastNonZeroIndex], nums[curr]);
				lastNonZeroIndex++;
			}
		}
	}

	void moveZeroes_2(std::vector<int>& nums)
	{
		int wIndex = 0;
			
		for (auto i = 0; i < nums.size(); ++i)
		{
			// wIndex�� ����Ű�� ���� 0�� �ƴϸ� shift�ϴ°��� �ݺ�.
			if (nums[i] != 0)
			{
				nums[wIndex] = nums[i];
				wIndex++;
			}
		}

		for (; wIndex < nums.size(); ++wIndex)
		{
			nums[wIndex] = 0;
		}
	}
};