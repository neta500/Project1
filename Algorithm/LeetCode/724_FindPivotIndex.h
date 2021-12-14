#pragma once
#include <vector>
#include <numeric>

// brute force(전체 순회)를 쓰면 O(n^2)인데..
// Sliding 개념을 알면 최적화를 할 수 있다.
// 한번 루프 돌때마다 leftSum과 rightSum을 계산해주면됨.

class Solution
{
public:
	// O(n)
	int pivotIndex(std::vector<int>& nums)
	{
		int leftSum = 0;
		int rightSum = std::accumulate(nums.begin(), nums.end(), 0);

		int temp = 0;

		for (auto i = 0; i < nums.size(); ++i)
		{
			int num = nums[i];

			// brute force에서는 for loop 마다 다시 loop를 돌면서 leftSum과 rightSum을 구했는데,
			// loop를 돌때마다 sum을 업데이트해주면 한번의 loop로 문제를 해결할 수 있음. 
			rightSum -= num;
			leftSum += temp;

			if (leftSum == rightSum)
			{
				return i;
			}

			temp = num;
		}

		return -1;
	}

	// O(n^2)
	int pivotIndex_bruteForce(std::vector<int>& nums)
	{
		if (std::accumulate(nums.begin(), nums.end(), 0) == 0)
		{
			return -1;
		}

		for (auto i = 0; i < nums.size(); ++i)
		{
			int leftSum = 0, rightSum = 0;
			if (i == 0)
			{
				rightSum = std::accumulate(nums.begin(), nums.end(), 0) - nums[i];
			}
			else if (i == nums.size() - 1)
			{
				leftSum = std::accumulate(nums.begin(), nums.end(), 0) - nums[i];
			}
			else
			{
				for (auto j = 0; j < i; ++j)
				{
					leftSum += nums[j];
				}

				for (auto j = i + 1; j < nums.size(); ++j)
				{
					rightSum += nums[j];
				}
			}

			if (leftSum == rightSum)
			{
				return i;
			}
		}

		return -1;
	}
};