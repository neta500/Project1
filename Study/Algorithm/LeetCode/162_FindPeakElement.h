#pragma once
#include <vector>
#include <numeric>
#include <set>

// 1. 그냥 O(n)으로 하나하나 비교해가며, max값과, 그 주위 값을 찾는다.
// 2. binary search를 이용한다. O(logn)

class Solution 
{
public:
    int findPeakElement(std::vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right)
        {
            int pivot = (left + right) / 2;
            if (nums[pivot] < nums[pivot + 1])
            {
                left = pivot + 1;
            }
            else
            {
                right = pivot;
            }
        }

        return left;
    }
};