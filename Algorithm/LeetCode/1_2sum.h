#pragma once
#include <vector>
#include <unordered_map>

// 1. brute force ��� �������� ���ؼ�, �����ϴ� �������� index�� üũ. O(n^2)
// 2. sorting�� ��� O(nlogn). ���� �� left, right���� index�� �������鼭 ���� üũ.
// 3. hash_map�� ��� O(n) + space O(n).

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