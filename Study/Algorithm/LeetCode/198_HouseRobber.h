#pragma once
#include <vector>

// #dp

class Solution {
public:
    int rob_dp(std::vector<int>& nums) {
        std::vector<int> dp(nums.size());

        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);

        for (int i = 2; i < nums.size(); ++i)
        {
            dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[nums.size() - 1];
    }

    int rob(std::vector<int>& nums) {
        if (nums.size() == 1) return nums[0];

        int prevMax = std::max(nums[0], nums[1]);
        int prevMax2 = nums[0];
        int currentMax = prevMax;

        for (int i = 2; i < nums.size(); ++i)
        {
            currentMax = std::max(prevMax, prevMax2 + nums[i]);
            prevMax2 = prevMax;
            prevMax = currentMax;
        }

        return currentMax;
    }

    // [2,7,9,3,1] -> (2,9,1)을 rob해서 12    
    // prevMax2는 인덱스의 바로 앞의 값을 저장해서, 다음 인덱스랑 합쳐서 비교하기 위해서 쓰는 변수
    // init : currentMax = 7, prevMax = 7, prevMax2 = 2
    // i = 2, 2 + 9와 7을 비교해서 currentMax = 11, prevMax = 11, prevMax2 = 7
    // i = 3, 7 + 3을 해도 11보다 작기 때문에 currentMax = 11, prevMax = 11, prevMax2 = 11
    // i = 4, prevMax2에 1을 더하면 끝.
};