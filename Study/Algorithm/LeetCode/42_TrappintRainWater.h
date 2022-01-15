#pragma once
#include <vector>

// 그림보면 바로 이해되는 문제. 검은색 칸이 주어졌을때, 물을 채울 수 있는 공간의 합을 구해야함.
// [0,1,0,2,1,0,1,3,2,1,2,1] -> 6칸의 물을 채울 수 있다.
// 1. brute_force
// 2. two pointers

class Solution {
public:
    int trap_bruteforce(std::vector<int>& height) {
        int ans = 0;
        int left_max = 0, right_max = 0;
        for (int i = 0; i < height.size(); ++i)
        {
            for (int j = i; j >= 0; --j)
            {
                left_max = std::max(left_max, height[j]);
            }

            for (int j = i; j < height.size(); ++j)
            {
                right_max = std::max(right_max, height[j]);
            }

            ans += std::min(left_max, right_max) - height[i];
        }

        return ans;
    }

    int trap_twopointers(std::vector<int>& height)
    {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int left_max = 0, right_max = 0;

        while (left < right)
        {
	        if (height[left] < height[right])
	        {
		        if (height[left] >= left_max)
		        {
                    left_max = height[left];
		        }
                else
                {
                    ans += left_max - height[left];
                }

                ++left;
	        }
            else
            {
	            if (height[right] >= right_max)
	            {
                    right_max = height[right];
	            }
                else
                {
                    ans += right_max - height[right];
                }

                --right;
            }
        }

        return ans;
    }
};