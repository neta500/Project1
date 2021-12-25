#pragma once
#include <vector>

// 2차원 정사각형 배열을 90도 우측으로 돌려라. 

class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        const int n = matrix.size();
        for (int i = 0; i < n / 2; ++i)
        {
            for (int j = 0; j < (n + 1) / 2; ++j)
            {
                int temp = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - j - 1];
                matrix[n - 1 - i][n - j - 1] = matrix[j][n - 1 - i];
                matrix[j][n - 1 - i] = matrix[i][j];
                matrix[i][j] = temp;
            }
        }
    }
};