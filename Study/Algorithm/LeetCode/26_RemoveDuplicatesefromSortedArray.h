#pragma once
#include <vector>

// [0,0,1,1,2] -> [0,1,2,_,_]
// [0,1,0,1,2]
// [0,1,1,0,2]
// [0,1,2,0,1]

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        int count = 0;
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] == nums[i - 1])            
            {
                count++;
            }
            else
            {
                nums[i - count] = nums[i];
            }
        }

        return nums.size() - count;
    }
};