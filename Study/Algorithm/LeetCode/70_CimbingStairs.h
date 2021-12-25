#pragma once
#include <vector>

// �Ǻ���ġ�� ������ dp ����
// n�� ���� �ö󰡱����� ����� ��
// n�� = n-1�� + n-2��

class Solution {
public:
    int climbStairs(int n) {
        std::vector<int> vec(n + 3, 0);

        // 1�� �ö󰡴µ� ����� �� 1
        vec[1] = 1;
        // 2�� �ö󰡴µ� ����� �� 2 (1+1 // 2)
        vec[2] = 2;        

        // n�� �ö󰡴µ� ����� �� n = n-1�� ����� �� + n-2�� ����� ��
        for (auto i = 3; i <= n; ++i)
        {
            vec[i] = vec[i - 1] + vec[i - 2];
        }

        return vec[n];
    }
};