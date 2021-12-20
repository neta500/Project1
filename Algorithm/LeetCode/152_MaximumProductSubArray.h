#pragma once
#include <vector>

class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        int globalMaxProduct = nums[0], currMaxProduct = nums[0], currMinProduct = nums[0];

        for (auto i = 1; i < nums.size(); ++i)
        {
            if (nums[i] < 0)
            {
                std::swap(currMaxProduct, currMinProduct);
            }

            currMaxProduct = std::max(nums[i], currMaxProduct * nums[i]);
            currMinProduct = std::min(nums[i], currMinProduct * nums[i]);
            globalMaxProduct = std::max(globalMaxProduct, currMaxProduct);
        }

        return globalMaxProduct;
    }
};