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

        // 이미 와본곳은 패스
        if (grid[i][j] == '2' || grid[i][j] == '0')
        {
            return;
        }

        // 한번 간곳은 2로 체크한다.
        grid[i][j] = '2';

        DFS(grid, i + 1, j); // 동
        DFS(grid, i - 1, j); // 서
        DFS(grid, i, j + 1); // 남
        DFS(grid, i, j - 1); // 북
    }

    int numIslands(std::vector<std::vector<char>>& grid) {
        int islandCount = 0;

        // (0,0)부터 DFS 탐색
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[i].size(); ++j)
            {
                // 노드가 1이면 island임.
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