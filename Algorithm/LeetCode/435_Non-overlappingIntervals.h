#pragma once
#include <vector>
#include <algorithm>

// #greedy #interval
// �ּ����� �迭 ������ �ߺ��Ǵ� ������ ���ִ¹�
// end�� ���� ������� sorting �� ���ʷ� ��ġ�� �κ��� �����Ѵ�.

class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        int count = 0;

        auto sort = [](const auto& vecA, const auto& vecB)
        {
            // end�� ���� ������ ����
            return vecA[1] < vecB[1];
        };

        std::sort(intervals.begin(), intervals.end(), sort);

        // 0���� �߾��µ� ������ ���ͼ� �ٲ�
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