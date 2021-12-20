#pragma once
#include <vector>
#include <numeric>

class Solution {
public:
    bool canPartition(std::vector<int>& nums) {
        sum = std::accumulate(nums.begin(), nums.end(), sum);
        return (sum % 2 == 0) && solve(nums, sum / 2);
    }

private:
    int sum = 0;
    bool solve(std::vector<int>& nums, int s)
    {
        int size = nums.size();
        std::vector<bool> dp(s + 1, false);
        dp[0] = true;

        for (const auto num : nums)
        {
            for (int j = s; j >= num; --j)
            {
                if (dp[j - num] || j == num)
                {
                    dp[j] = true;
                }
            }
        }

        return dp[s];
    }
};