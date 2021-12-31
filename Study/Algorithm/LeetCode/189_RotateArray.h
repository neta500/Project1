#pragma once
#include <vector>
#include <algorithm>

// [1,2,3,4,5,6,7], 3 -> [5,6,7,1,2,3,4]
// ù��° ���� 1�� k�� rotate������ ��ġ�� �˸� �������� �˾Ƽ� ä�� �� �ִ�.
// k < 7�� ��� 1�� index�� k�� ���� �ڸ�, k >=7 �ΰ�� k�� 7�� ���� �������� index

// std::rotate

class Solution {
public:
    void rotate(std::vector<int>& nums, int k) {
        if (nums.size() == 1) return;
        if (k >= 7) k %= 7;
        std::vector<int> temp = nums;

        for (int i = 0; i < nums.size(); i++)
        {
            nums[(i + k) % nums.size()] = temp[i];
        }
    }

    void rotate_2(std::vector<int>& nums, int k) {
        std::rotate(nums.rbegin(), nums.rbegin()+ k%nums.size(), nums.rend());
    }
};