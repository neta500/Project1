#pragma once
#include <vector>
#include <string>

// <backtracking>
// n�� 1�϶�, 2�϶�, 3�϶� ... n�� �������Ѱ��鼭 �����غ��°� first.
// ���� ���ݷ�Ʈ ��, �ϳ��� �࿡���� ������ �ϳ��� ���� ������ �� �ִ�.

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
        // ���� üũ
        if (row == num)
        {
            result.push_back(nQueens);
            return;
        }

        // ���� �������Ѱ��� recurrsive call
        for (int col = 0; col != num; ++col)
        {
            // ���� ���� �� �ִ°�? (�̹� ������ ���� ��ġ ��)
            if (isValid(nQueens, row, col))
            {
                nQueens[row][col] = 'Q'; // ���� �� row�� �������Ѽ� ���� row üũ
                solveNQueens(nQueens, row + 1); // üũ
                nQueens[row][col] = '.'; // ����Դٴ°� �ش� row����üũ�� false��°��̹Ƿ� ������
            }
        }
    }

    // ���� �� �ִ� �� �˻��ϴ� �κ��� �̷����ϸ� O(n)�̳�, hash_set�� �̿��ϸ� O(1)
    bool isValid(std::vector<std::string>& nQueens, int row, int col)
    {
        //check if the column had a queen before.
        for (int i = 0; i != row; ++i)
            if (nQueens[i][col] == 'Q')
                return false;
        //check if the 45�� diagonal had a queen before.
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
            if (nQueens[i][j] == 'Q')
                return false;
        //check if the 135�� diagonal had a queen before.
        for (int i = row - 1, j = col + 1; i >= 0 && j < num; --i, ++j)
            if (nQueens[i][j] == 'Q')
                return false;
        return true;
    }
};