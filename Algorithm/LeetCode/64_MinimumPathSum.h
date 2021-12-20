#pragma once
#include <vector>

class Solution {
public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        for (auto i = 0; i < grid.size(); ++i)
        {
            for (auto j = 0; j < grid[0].size(); ++j)
            {
                if (i == 0 && j == 0) continue;

                if (i == 0)
                {
                    grid[i][j] += grid[i][j - 1];
                }
                else if (j == 0)
                {
                    grid[i][j] += grid[i - 1][j];
                }
                else
                {
                    if (grid[i - 1][j] > grid[i][j - 1])
                    {
                        grid[i][j] += grid[i][j - 1];
                    }
                    else
                    {
                        grid[i][j] += grid[i - 1][j];
                    }
                }
            }
        }

        return grid[grid.size() - 1][grid[0].size() - 1];
    }
};