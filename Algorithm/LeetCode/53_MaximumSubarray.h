#pragma once
#include <vector>

class Solution {
public:
    // iterative
    int maxSubArray_iterative(std::vector<int>& nums)
    {
        int globalMaxSum = nums[0], currMaxSum = nums[0];

        for (auto i = 1; i < nums.size(); ++i)
        {
            currMaxSum = std::max(nums[i], currMaxSum + nums[i]);
            globalMaxSum = std::max(currMaxSum, globalMaxSum);
        }

        return globalMaxSum;
    }


    // brute force
    int maxSubArray_bruteforce(std::vector<int>& nums) {
        int maxSum = INT_MIN;

        for (auto index1 = 0; index1 < nums.size(); ++index1)
        {
            int sum = nums[index1];            

            if (maxSum < sum)
            {
                maxSum = sum;
            }

            for (auto index2 = index1 + 1; index2 < nums.size(); ++index2)
            {
                sum += nums[index2];

                if (maxSum < sum)
                {
                    maxSum = sum;
                }
            }
        }

        return maxSum;
    }
};