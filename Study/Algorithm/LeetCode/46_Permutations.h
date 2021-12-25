#pragma once
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> ans;
        permute(ans, nums, 0);
        return ans;
    }

private:
    void permute(std::vector<std::vector<int>>& ans, std::vector<int> nums, int i)
    {
        if (i == nums.size())
        {
            ans.push_back(nums);
        }
        else
        {
            for (int j = i; j < nums.size(); j++)
            {
                std::swap(nums[i], nums[j]);
                permute(ans, nums, i + 1);
            }
        }
    }
};