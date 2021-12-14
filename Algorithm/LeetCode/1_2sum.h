#pragma once
#include <vector>
#include <unordered_map>

// 1. brute force 모든 순서쌍을 구해서, 만족하는 순서쌍의 index를 체크. O(n^2)
// 2. sorting을 사용 O(nlogn). 정렬 후 left, right에서 index를 좁혀가면서 합을 체크.
// 3. hash_map을 사용 O(n) + space O(n).

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> map;

        for (int i = 0; i < nums.size(); ++i)
        {
            map.emplace(nums[i], i);
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            int num = nums[i];
            int remain = target - num;
            if (const auto found = map.find(remain); found != map.cend())
            {
                int index = map[remain];
                if (index == i)
                {
                    continue;
                }
                return std::vector<int>{i, index};
            }
        }

        return std::vector<int>{};
    }
};