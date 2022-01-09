#pragma once
#include <algorithm>
#include <vector>
#include <unordered_map>

// 3�� ��ģ ���� 0�� ����� ��(triplet) ���ϱ�
// [-1,0,1,2,-1,-4] -> [-1,-1,2],[-1,0,1]
// 2sum�� ����������, two pointers, hash_map�� �����غ� �� �ִ�.

class Solution {
public:
	std::vector<std::vector<int>> threeSum_hashmap(std::vector<int>& nums)
	{
		std::sort(nums.begin(), nums.end());

		if (nums.size() < 3)
		{
			return {};
		}

		if (nums[0] > 0)
		{
			return {};
		}

		std::vector<std::vector<int>> result;

		std::unordered_map<int, int> map;
		for (int i = 0; i < nums.size(); ++i)
		{
			map[nums[i]] = i;
		}

		// i�� j ���� ���, ������ �ʿ��� ���� map���� ã�� ���
		for (int i = 0; i < nums.size() - 2; ++i)
		{
			if (nums[i] > 0)
			{
				break;
			}

			for (int j = i + 1; j < nums.size() - 1; ++j)
			{
				int required = -1 * (nums[i] + nums[j]);

				if (map.find(required) != map.cend() && map.find(required)->second > j)
				{
					result.push_back({ nums[i], nums[j], required });
				}

				j = map.find(nums[j])->second;
			}

			i = map.find(nums[i])->second;
		}

		return result;
	}

	std::vector<std::vector<int>> threeSum_twopointers(std::vector<int>& nums) {

		std::sort(nums.begin(), nums.end());

		if (nums.size() < 3)
		{
			return {};
		}

		if (nums[0] > 0)
		{
			return {};
		}

		std::vector<std::vector<int>> result;

		for (int i = 0; i < nums.size(); ++i)
		{
			if (nums[i] > 0)
			{
				break;
			}

			// index i���� ���� ���ڿ� �����ߴٸ� �ߺ� ��Ī�̹Ƿ� �н�.
			if (i > 0 && nums[i] == nums[i-1])
			{
				continue;
			}

			int left = i + 1;
			int right = nums.size() - 1;

			while (left < right)
			{
				const int sum = nums[i] + nums[left] + nums[right];						

				if (sum < 0)
				{
					left++;
				}
				else if (sum > 0)
				{
					right--;
				}
				else // sum == 0
				{
					result.push_back({ nums[i], nums[left], nums[right] });
					
					int leftNum = nums[left];
					int rightNum = nums[right];

					// [-1,-1,-1,0,1] ���� �ߺ��Ǵ� triplet�� ���� �� �ֱ� ������,
					// ���� ������� index�� �� �̵����ش�.
					while (left < right && nums[left] == leftNum) left++;
					while (left < right && nums[right] == rightNum) right--;
				}
			}
		}

		return result;
    }

};