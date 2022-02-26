#pragma once
#include <algorithm>
#include <vector>

// [1,4] [3,6], [2,8] -> [3,6]�� [2,8] �ȿ� �����ϹǷ�, ���� �� �ִ�.
// covered interval�� �� �������, ���� ������ ������ ����.

// brute force : ��� �������� �˻��ؼ�, covered���� üũ�Ѵ�.
// sorting : interval���� �����ؼ� �������� ��.

class Solution {
public:
    int removeCoveredIntervals(std::vector<std::vector<int>>& intervals) {
        // ������ �� �� start�� ��������, end�� ������������
        std::sort(intervals.begin(), intervals.end(), [](const auto x, const auto y)
        {
            if (x[0] != y[0]) return x[0] < y[0];
			return x[1] > y[1];
		});

        int prev = intervals[0][1];
        int count = 1;
        for (const auto& interval : intervals)
        {
            // ������ �س����� start ([0])�� ���� �ʿ䰡 ����.
            // end ([1])�� ���ؼ� covered���� Ȯ�� ����.
            // [2,8], [3,6]�� ���� ��, �׻� ���� 2,3�� ���ĵǾ��ֱ� ������,
            // 8���� 6�� �������� ���ؼ�, ������ ������ �����̴�.
            if (prev < interval[1])
            {
                prev = interval[1];
                count++;
            }
        }

        return count;
    }
};