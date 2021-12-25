#pragma once
#include <vector>
#include <numeric>

// brute force(��ü ��ȸ)�� ���� O(n^2)�ε�..
// Sliding ������ �˸� ����ȭ�� �� �� �ִ�.
// �ѹ� ���� �������� leftSum�� rightSum�� ������ָ��.

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

			// brute force������ for loop ���� �ٽ� loop�� ���鼭 leftSum�� rightSum�� ���ߴµ�,
			// loop�� �������� sum�� ������Ʈ���ָ� �ѹ��� loop�� ������ �ذ��� �� ����. 
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