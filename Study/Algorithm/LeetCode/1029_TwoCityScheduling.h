#pragma once
#include <vector>

// 2n 명의 사람이 a city, b city에 나눠서 인터뷰를 보러 가야한다.
// cost[i] = [aCost, bCost]
// [[10,20], [30,200], [400,50], [30,20]] -> 110
// 위 예의 경우 4명이 AABB 이렇게 나눠가야하는데, 10, 30, 50, 20 이렇게 가면된다.
// 딱봐도 greedy인데..

class Solution {
public:
    int twoCitySchedCost_greedy(std::vector<std::vector<int>>& costs) {

        // 각 city의 aCost, bCost의 diff로 정렬하는게 핵심 intuition이다.
        // aCityCost와 bCityCost가 많이 차이난다는것은, 그 중 작은 값을 골랐을 때
        // 그 값이 최적의 값이 된다는 것을 기대할 수 있다는 뜻이다.
        // 그렇기 때문에 diff로 sorting후 순서대로 min을 구하는 것.
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

        // recursive하게 cost를 구한다. O(2^n). 하지만 이러면 한번 계산했던 최적값을 반복해서 계산하게되는 문제가 있다.
        // 때문에 dp로 지나온 값을 기록해서, 최적화가 가능하다.
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