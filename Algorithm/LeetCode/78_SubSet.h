#pragma once
#include <vector>
class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<std::vector<int>> result = { {} };

        for (const auto num : nums)
        {
            int size = result.size();
            for (int i = 0; i < size; ++i)
            {
                result.emplace_back(result[i]);
                result.back().emplace_back(num);
            }
        }

        return result;
    }
};