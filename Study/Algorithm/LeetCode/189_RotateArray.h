#pragma once
#include <vector>
#include <algorithm>

// [1,2,3,4,5,6,7], 3 -> [5,6,7,1,2,3,4]
// 첫번째 숫자 1이 k번 rotate했을때 위치만 알면 나머지는 알아서 채울 수 있다.
// k < 7인 경우 1의 index에 k를 더한 자리, k >=7 인경우 k를 7로 나눈 나머지의 index

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