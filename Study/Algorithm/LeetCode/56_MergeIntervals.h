#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

// 1. ��� pair�� ���ؼ�, �����Ǵ°�� �����Ѵ�. O(n^2)
// 2. sorting�� �̿��Ѵ�. O(nlogn). ������ �ϰ�, �ѹ� ���鼭 ������ �������� ���ؼ� ������Ʈ�Ѵ�.

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