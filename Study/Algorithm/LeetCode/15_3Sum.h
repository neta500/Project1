#pragma once
#include <algorithm>
#include <vector>
#include <unordered_map>

// 3개 합친 값이 0인 경우의 수(triplet) 구하기
// [-1,0,1,2,-1,-4] -> [-1,-1,2],[-1,0,1]
// 2sum과 마찬가지로, two pointers, hash_map을 생각해볼 수 있다.

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

		// i와 j 페어로 잡고, 나머지 필요한 수를 map에서 찾는 방식
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

			// index i값이 이전 숫자와 동일했다면 중복 서칭이므로 패스.
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

					// [-1,-1,-1,0,1] 같이 중복되는 triplet이 있을 수 있기 때문에,
					// 값이 같은경우 index를 더 이동해준다.
					while (left < right && nums[left] == leftNum) left++;
					while (left < right && nums[right] == rightNum) right--;
				}
			}
		}

		return result;
    }

};