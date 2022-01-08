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

    // [2,7,9,3,1] -> (2,9,1)�� rob�ؼ� 12    
    // prevMax2�� �ε����� �ٷ� ���� ���� �����ؼ�, ���� �ε����� ���ļ� ���ϱ� ���ؼ� ���� ����
    // init : currentMax = 7, prevMax = 7, prevMax2 = 2
    // i = 2, 2 + 9�� 7�� ���ؼ� currentMax = 11, prevMax = 11, prevMax2 = 7
    // i = 3, 7 + 3�� �ص� 11���� �۱� ������ currentMax = 11, prevMax = 11, prevMax2 = 11
    // i = 4, prevMax2�� 1�� ���ϸ� ��.
};