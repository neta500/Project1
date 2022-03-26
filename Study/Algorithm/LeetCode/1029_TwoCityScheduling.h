#pragma once
#include <vector>

// 2n ���� ����� a city, b city�� ������ ���ͺ並 ���� �����Ѵ�.
// cost[i] = [aCost, bCost]
// [[10,20], [30,200], [400,50], [30,20]] -> 110
// �� ���� ��� 4���� AABB �̷��� ���������ϴµ�, 10, 30, 50, 20 �̷��� ����ȴ�.
// ������ greedy�ε�..

class Solution {
public:
    int twoCitySchedCost_greedy(std::vector<std::vector<int>>& costs) {

        // �� city�� aCost, bCost�� diff�� �����ϴ°� �ٽ� intuition�̴�.
        // aCityCost�� bCityCost�� ���� ���̳��ٴ°���, �� �� ���� ���� ����� ��
        // �� ���� ������ ���� �ȴٴ� ���� ����� �� �ִٴ� ���̴�.
        // �׷��� ������ diff�� sorting�� ������� min�� ���ϴ� ��.
        std::sort(costs.begin(), costs.end(),
            [](const std::vector<int>& a, const std::vector<int>& b)
            {
                return a[1] - a[0] > b[1] - b[0];
            });

        int size = costs.size();
        int minCost = 0;
                
        for (int i = 0; i < costs.size(); ++i)
        {
	        if (i < size / 2)
	        {
                minCost += costs[i][0];
	        }
            else
            {
                minCost += costs[i][1];
            }
        }

        return minCost;
    }

    // bruteforce solution O(2^n), dp : O(n^2)
    int GetMinCost(int index, int& size, int aCityLeft, int bCityLeft,
        std::vector<std::vector<int>>& costs,
        std::vector<std::vector<int>>& dp)
    {
	    if (index == size)
	    {
            return 0;
	    }

        if (aCityLeft <= 0 && bCityLeft <= 0)
        {
            return 0;
        }
        
        if (dp[aCityLeft][bCityLeft] != -1)
        {
            return dp[aCityLeft][bCityLeft];
        }

        int minCost = INT_MAX;

        // recursive�ϰ� cost�� ���Ѵ�. O(2^n). ������ �̷��� �ѹ� ����ߴ� �������� �ݺ��ؼ� ����ϰԵǴ� ������ �ִ�.
        // ������ dp�� ������ ���� ����ؼ�, ����ȭ�� �����ϴ�.
        if (aCityLeft > 0)
        {
            minCost = std::min(minCost, costs[index][0] + GetMinCost(index + 1, size, aCityLeft - 1, bCityLeft, costs, dp));
        }

        if (bCityLeft > 0)
        {
            minCost = std::min(minCost, costs[index][1] + GetMinCost(index + 1, size, aCityLeft, bCityLeft - 1, costs, dp));
        }

        dp[aCityLeft][bCityLeft] = minCost;

        return minCost;
    }

    int twoCitySchedCost_dp(std::vector<std::vector<int>>& costs) {        		
        int size = static_cast<int>(costs.size());
        std::vector<std::vector<int>> dp(size + 1, std::vector<int>(size + 1, -1));
        return GetMinCost(0, size, size / 2, size / 2, costs, dp);
    }
};