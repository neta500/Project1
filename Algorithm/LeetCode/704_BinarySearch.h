#pragma once
#include <vector>

// sorted array와 target이 주어졌을 때, 타겟이 array에 있는 경우 index를, 없는경우 -1을 출력. O(logn)의 complexity를 가져야함.

// binary search는 그 술게임중에 업다운? 그거랑 완전 똑같다. 배열의 가운데를 찍어서 타겟이 그 숫자보다 왼쪽에 있냐, 오른쪽에 있냐를 판단하는 작업을 반복하는것.

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