#pragma once
#include <vector>

// [7,1,5,3,6,4] 1�϶� �缭 6�϶� �Ǵ� -> 5
// [7,6,4,3,1] �̵� ���� -> 0
// 1. O(n^2)�� ��ȸ�ϸ鼭 ���� ���� profit�� ã�´�
// 2. �̰ɾ�� �Ϲ�ȭ����.. One Pass O(n), min/max�� ������ ������ ������ �Ẹ��.

class Solution{
public:
    int maxProfit(std::vector<int>&prices) {
        int maxProfit = 0;
        int minPrice = INT_MAX;
        for (int i = 0; i < prices.size(); ++i)
        {
            minPrice = std::min(prices[i], minPrice);
            maxProfit = std::max(prices[i] - minPrice, maxProfit);
        }

        return maxProfit;
    }
};

// 122. Best Time to Buy and Sell stock 2
// [7,1,5,3,6,4] �ִ��̵� 1->5(4), 3->6(3), 7�̵�
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