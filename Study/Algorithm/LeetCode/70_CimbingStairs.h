#pragma once
#include <vector>

// 피보나치랑 동일한 dp 문제
// n층 까지 올라가기위한 경우의 수
// n층 = n-1층 + n-2층

class Solution {
public:
    int climbStairs(int n) {
        std::vector<int> vec(n + 3, 0);

        // 1층 올라가는데 경우의 수 1
        vec[1] = 1;
        // 2층 올라가는데 경우의 수 2 (1+1 // 2)
        vec[2] = 2;        

        // n층 올라가는데 경우의 수 n = n-1층 경우의 수 + n-2층 경우의 수
        for (auto i = 3; i <= n; ++i)
        {
            vec[i] = vec[i - 1] + vec[i - 2];
        }

        return vec[n];
    }
};