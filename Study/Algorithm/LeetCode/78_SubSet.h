#pragma once
#include <vector>

// 배열의 모든 subarray를 구하는 문제.
// 앞에 구해놓은 subarray를 다시 이용하는 방법으로, O(n * 2^n)으로 구할 수 있다.
// 기본적으로 subset(부분집합)은 2^n개이다.
// backtracking(recurrsion), iterative, bitmask로 풀 수 있음.

class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<std::vector<int>> result = { {} };

        for (const auto num : nums)
        {
            int size = result.size();
            for (int i = 0; i < size; ++i)
            {
                result.emplace_back(result[i]);
                result.back().emplace_back(num);
            }
        }

        return result;
    }
};