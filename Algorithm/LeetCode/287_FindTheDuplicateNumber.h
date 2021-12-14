#pragma once
#include <vector>

// 1. brute force : ��� �������� ���ؼ� ���� �� ������ ã�Ƴ� O(n^2)
// 2. sorting : ���� �� �ѹ��� ���鼭 �������� ������ ã�Ƴ� �����ϴµ� ��� ��� O(nlogn)
// 3. ������ array�� �����, flag�� �÷����� ī����. O(n) + space O(n)
// 4. ������ array�� ������ �ʰ�, �־��� array���� flag�� ī�����Ѵ�. O(n) + space O(1)
// 5. swap
// 6. Floyd's Tortoise and Hare

class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[std::abs(nums[i])] < 0)
            {
                return std::abs(nums[i]);
            }
            else
            {
                nums[std::abs(nums[i])] *= -1;
            }
        }

        return 0;
    }
};