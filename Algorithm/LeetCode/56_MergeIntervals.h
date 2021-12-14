#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

// 1. 모든 pair를 비교해서, 머지되는경우 머지한다. O(n^2)
// 2. sorting을 이용한다. O(nlogn). 정렬을 하고, 한번 돌면서 끝점과 시작점만 비교해서 업데이트한다.

class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end());

        std::vector<std::vector<int>> merged;

        for (const auto& vec : intervals)
        {
            if (merged.empty() || merged.back()[1] < vec[0])
            {
                merged.emplace_back(vec);
            }
            else
            {
                merged.back()[1] = std::max(merged.back()[1], vec[1]);
            }
        }

        return merged;
    }
};