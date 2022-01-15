#pragma once
#include <vector>

// #greedy
// 각 index에서 원소값만큼 점프가 가능하다.
// [2,3,1,1,4] -> index 0에서 2칸까지 점프가능, 1점프-> index 1에서 3점프해서 last까지 가능


class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        int farest = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
	        if (farest < i)
	        {
                return false;
	        }

            farest = std::max(i + nums[i], farest);
        }

        return true;
    }
};