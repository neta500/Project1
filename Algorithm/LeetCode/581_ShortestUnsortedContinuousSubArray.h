#pragma once
#include <vector>
#include <algorithm>

// 1. vec�� �����ϰ�, ���� ���ĸ� ���ؼ� �ٸ� startIndex~endIndex�� üũ�Ѵ�. O(nlogn)
// 2. ���̰� ó�������Ѱ� �´µ� startIndex, endIndex ó���� unsorted �ɸ��� �� üũ. O(n)

class Solution {
public:
    int findUnsortedSubarray(std::vector<int>& nums) {
        int min = INT_MAX, max = INT_MIN;
        bool unsorted = false;

        for (auto i = 1; i < nums.size(); ++i)
        {
            if (nums[i] < nums[i - 1])
            {
                unsorted = true;
            }

            if (unsorted)
            {
                min = std::min(min, nums[i]);
            }
        }

        unsorted = false;

        for (int i = static_cast<int>(nums.size()) - 2; i >= 0; --i)
        {
            if (nums[i] > nums[i + 1])
            {
                unsorted = true;
            }

            if (unsorted)
            {
                max = std::max(max, nums[i]);
            }
        }

        int left, right;
        for (left = 0; left < nums.size(); ++left)
        {
            if (min < nums[left])
            {
                break;
            }
        }

        for (right = nums.size() - 1; right >= 0; right--)
        {
            if (max > nums[right])
            {
                break;
            }
        }

        return right - left < 0 ? 0 : right - left + 1;
    }
};