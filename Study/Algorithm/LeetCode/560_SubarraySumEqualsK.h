#pragma once
#include <vector>
#include <unordered_map>

// 1. brute force 모든 subarray를 구한다. O(n^3)
// 2. hash_map O(n) nums를 순회하면서, sum에 대한 기록을 전부 hash_map에 저장한다.

class Solution {
public:
	int subarraySum(std::vector<int>& nums, int k) {
		std::unordered_map<int, int> map; // sum, count
		map.emplace(0, 1);
		int count = 0;
		int sum = 0;

		for (const int num : nums)
		{
			sum += num;

			if (map.find(sum - k) != map.end())
			{
				count += map[sum - k];
			}

			map[sum]++;
		}

		return count;
	}

    int subarraySum_bruteforce(std::vector<int>& nums, int k) {
        int count = 0;

        for (int start = 0; start < nums.size(); ++start)
        {
            int sum = 0;

	        for (int end = start + 1; end < nums.size(); ++end)
	        {
		        for (int i = start; i < end; ++i)
		        {
					sum += nums[i];
		        }

				if (sum == k)
				{
					count++;					
				}
	        }
        }

		return count;
    }
};