#pragma once
#include <vector>
#include <string>

// <backtracking>
// n이 1일때, 2일때, 3일때 ... n을 증가시켜가면서 생각해보는게 first.
// 퀸의 공격루트 상, 하나의 행에서는 무조건 하나의 퀸만 존재할 수 있다.

class Solution {
    std::vector<std::vector<std::string>> result;
    int num;
    
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        num = n;
        std::vector<std::string> nQueens(n, std::string(n, '.'));
        solveNQueens(nQueens, 0);
        return result;
    }

    void solveNQueens(std::vector<std::string>& nQueens, int row)
    {
        // 조건 체크
        if (row == num)
        {
            result.push_back(nQueens);
            return;
        }

        // 행을 증가시켜가며 recurrsive call
        for (int col = 0; col != num; ++col)
        {
            // 퀸을 놓을 수 있는가? (이미 놓여진 퀸과 위치 비교)
            if (isValid(nQueens, row, col))
            {
                nQueens[row][col] = 'Q'; // 놓은 후 row를 증가시켜서 다음 row 체크
                solveNQueens(nQueens, row + 1); // 체크
                nQueens[row][col] = '.'; // 여기왔다는건 해당 row조건체크가 false라는것이므로 지워줌
            }
        }
    }

    // 놓을 수 있는 지 검사하는 부분은 이렇게하면 O(n)이나, hash_set을 이용하면 O(1)
    bool isValid(std::vector<std::string>& nQueens, int row, int col)
    {
        //check if the column had a queen before.
        for (int i = 0; i != row; ++i)
            if (nQueens[i][col] == 'Q')
                return false;
        //check if the 45° diagonal had a queen before.
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
            if (nQueens[i][j] == 'Q')
                return false;
        //check if the 135° diagonal had a queen before.
        for (int i = row - 1, j = col + 1; i >= 0 && j < num; --i, ++j)
            if (nQueens[i][j] == 'Q')
                return false;
        return true;
    }
};