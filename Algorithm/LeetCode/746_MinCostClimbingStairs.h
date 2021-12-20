#pragma once
#include <vector>

// n������ �ö󰡴� cost
// = std::min(n-1������ �ö󰡴� cost + n-1���� cost, n-2������ �ö󰡴� cost + n-2���� cost)

class Solution {
public:
    int minCostClimbingStairs(std::vector<int>& cost) {
        for (auto i = 2; i < cost.size(); ++i)
        {
            cost[i] = cost[i] + std::min(cost[i - 1], cost[i - 2]);
        }

        return std::min(cost[cost.size() - 1], cost[cost.size() - 2]);
    }
};