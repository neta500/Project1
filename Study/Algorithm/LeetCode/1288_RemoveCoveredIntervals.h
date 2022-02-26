#pragma once
#include <algorithm>
#include <vector>

// [1,4] [3,6], [2,8] -> [3,6]은 [2,8] 안에 존재하므로, 지울 수 있다.
// covered interval을 다 지우고나서, 남은 원소의 개수를 리턴.

// brute force : 모든 순서쌍을 검색해서, covered인지 체크한다.
// sorting : interval들을 정렬해서 원루프로 비교.

class Solution {
public:
    int removeCoveredIntervals(std::vector<std::vector<int>>& intervals) {
        // 정렬을 할 때 start는 오름차순, end는 내림차순으로
        std::sort(intervals.begin(), intervals.end(), [](const auto x, const auto y)
        {
            if (x[0] != y[0]) return x[0] < y[0];
			return x[1] > y[1];
		});

        int prev = intervals[0][1];
        int count = 1;
        for (const auto& interval : intervals)
        {
            // 정렬을 해놓으면 start ([0])는 비교할 필요가 없다.
            // end ([1])만 비교해서 covered인지 확인 가능.
            // [2,8], [3,6]을 비교할 때, 항상 앞의 2,3은 정렬되어있기 때문에,
            // 8보다 6이 작은지만 비교해서, 작으면 무조건 포함이다.
            if (prev < interval[1])
            {
                prev = interval[1];
                count++;
            }
        }

        return count;
    }
};