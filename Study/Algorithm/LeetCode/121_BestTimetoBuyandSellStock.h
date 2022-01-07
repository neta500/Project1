#pragma once
#include <vector>

// [7,1,5,3,6,4] 1일때 사서 6일때 판다 -> 5
// [7,6,4,3,1] 이득 못봄 -> 0
// 1. O(n^2)로 순회하면서 가장 높은 profit을 찾는다
// 2. 이걸어떻게 일반화하지.. One Pass O(n), min/max가 문제에 나오면 변수로 써보자.

class Solution{
public:
    int maxProfit(std::vector<int>&prices) {
        int maxProfit = 0;
        int minPrice = INT_MAX;
        for (int i = 0; i < prices.size(); ++i)
        {
            minPrice = std::min(prices[i], minPrice);
            maxProfit = std::max(prices[i] - minPrice, maxProfit);

            // i = 0, minPrice 7, maxProfit 0 (7에 사서 7에 팜)
            // i = 1, minPrice 1, maxProfit 0 (1에 사서 1에 팜)
            // i = 2, minPrice 1, maxProfit 4 (1에 사서 5에 팜)
            // i = 3, minPrice 1, maxProfit 4 (1에 사서 5에 팜)
            // i = 4, minPrice 1, maxProfit 5 (1에 사서 6에 팜) -> 최대 이득
            // ...
        }

        return maxProfit;
    }
};

// 122. Best Time to Buy and Sell stock 2
// [7,1,5,3,6,4] 최대이득 1->5(4), 3->6(3), 7이득
// [1,2,3,4,5] 1->5(4)

class Solution_2 {
public:
    int maxProfit(std::vector<int>& prices) {
        int maxProfit = 0;
        for (int i = 1; i < prices.size(); ++i)
        {
            if (prices[i] > prices[i - 1])
            {
                maxProfit += prices[i] - prices[i - 1];
            }
        }

        return maxProfit;
    }
};