#pragma once
#include <vector>

// sorted array�� target�� �־����� ��, Ÿ���� array�� �ִ� ��� index��, ���°�� -1�� ���. O(logn)�� complexity�� ��������.

// binary search�� �� �������߿� ���ٿ�? �װŶ� ���� �Ȱ���. �迭�� ����� �� Ÿ���� �� ���ں��� ���ʿ� �ֳ�, �����ʿ� �ֳĸ� �Ǵ��ϴ� �۾��� �ݺ��ϴ°�.

class Solution
{
public:
	int search(std::vector<int>& nums, int target)
	{
		int leftIndex = 0;
		int rightIndex = nums.size() - 1;

		while (leftIndex <= rightIndex)
		{
			const int middleIndex = (leftIndex + rightIndex) / 2;
			const int middleValue = nums[middleIndex];

			if (middleValue == target)
			{
				return middleIndex;
			}
			else if (middleValue < target)
			{
				leftIndex = middleIndex + 1;
			}
			else // middleValue > target
			{
				rightIndex = middleIndex - 1;
			}
		}

		return -1;
	}
};