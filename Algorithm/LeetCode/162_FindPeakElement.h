#pragma once
#include <vector>
#include <numeric>
#include <set>

// 1. �׳� O(n)���� �ϳ��ϳ� ���ذ���, max����, �� ���� ���� ã�´�.
// 2. binary search�� �̿��Ѵ�. O(logn)

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