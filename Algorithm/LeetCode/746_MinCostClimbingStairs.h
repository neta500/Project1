#pragma once
#include <vector>

// n층까지 올라가는 cost
// = std::min(n-1층까지 올라가는 cost + n-1층의 cost, n-2층까지 올라가는 cost + n-2층의 cost)

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