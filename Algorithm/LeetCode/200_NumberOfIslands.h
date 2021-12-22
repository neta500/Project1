#pragma once
#include <vector>

class Solution {
public:
    void DFS(std::vector<std::vector<char>>& grid, int i, int j)
    {
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size())
        {
            return;
        }

        // �̹� �ͺ����� �н�
        if (grid[i][j] == '2' || grid[i][j] == '0')
        {
            return;
        }

        // �ѹ� ������ 2�� üũ�Ѵ�.
        grid[i][j] = '2';

        DFS(grid, i + 1, j); // ��
        DFS(grid, i - 1, j); // ��
        DFS(grid, i, j + 1); // ��
        DFS(grid, i, j - 1); // ��
    }

    int numIslands(std::vector<std::vector<char>>& grid) {
        int islandCount = 0;

        // (0,0)���� DFS Ž��
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[i].size(); ++j)
            {
                // ��尡 1�̸� island��.
                if (grid[i][j] == '1')
                {
                    DFS(grid, i, j);
                    islandCount++;
                }
            }
        }

        return islandCount;
    }
};