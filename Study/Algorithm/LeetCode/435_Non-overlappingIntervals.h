#pragma once
#include <vector>
#include <algorithm>

// #greedy #interval
// 최소한의 배열 삭제로 중복되는 구간을 없애는법
// end가 작은 순서대로 sorting 후 차례로 겹치는 부분을 삭제한다.

class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        int count = 0;

        auto sort = [](const auto& vecA, const auto& vecB)
        {
            // end가 작은 순서로 정렬
            return vecA[1] < vecB[1];
        };

        std::sort(intervals.begin(), intervals.end(), sort);

        // 0으로 했었는데 음수도 들어와서 바꿈
        int selected_end = INT_MIN;

        for (const auto& interval : intervals)
        {
            if (selected_end == INT_MIN)
            {
                selected_end = interval[1];
                continue;
            }

            if (selected_end > interval[0])
            {
                count++;
            }
            else
            {
                selected_end = interval[1];
            }
        }

        return count;
    }
};