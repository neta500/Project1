#pragma once
#include <vector>

// coins = [1,2,5], amount = 11일때
// F(11) = std::min(F(11-1), F(11-2), F(11-5)) + 1이라고 할 수 있다.

class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        std::vector<int> vec(amount + 1, INT_MAX);

        vec[0] = 0;

        for (const int coin : coins)
        {
            for (auto i = coin; i <= amount; ++i)
            {
                if (vec[i - coin] != INT_MAX)
                {
                    vec[i] = std::min(vec[i], vec[i - coin] + 1);
                }
            }
        }

        return vec[amount] == INT_MAX ? -1 : vec[amount];
    }
};