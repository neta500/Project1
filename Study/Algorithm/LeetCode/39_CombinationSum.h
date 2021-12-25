#pragma once
#include <vector>

class Solution {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    int sum = 0;
    int m_target = 0;
public:
    void function(std::vector<int>& candidates, int index)
    {
        if (sum > m_target) return;
        if (sum == m_target)
        {
            result.push_back(current);
        }

        for (int i = index; i < candidates.size(); ++i)
        {
            sum += candidates[i];
            current.push_back(candidates[i]);
            function(candidates, i);
            sum -= candidates[i];
            current.pop_back();
        }
    }

    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        m_target = target;
        function(candidates, 0);
        return result;
    }
};

// current vector 기준
// [2] -> 2
// [2, 2] -> 4
// [2, 2, 2] -> 6
// [2, 2, 2, 2] -> 8, 7보다 크므로 마지막 2를 빼고 candidates index++
// [2, 2, 2, 3] -> 9, 7보다 크므로 마지막 3을 빼고 candidates index++
// [2, 2, 2, 6] -> ...
// [2, 2, 2, 7] -> ...
// candidates를 다 돌았으므로, recurrsion 한단계 앞으로 가서 3번째 칸의 index++
// [2, 2, 3] -> 7 만족하므로 result에 push
// [2, 2, 6] -> 8, 7보다 크므로 마지막 6을 빼고 cadidates index++
// [2, 2, 7] -> 9, 7보다 크므로 마지막 7을 빼고 cadidates index++
// candidates를 다 돌았으므로, recurrsion 한단계 앞으로 가서 2번째 칸의 index++
// [2, 3] -> 5
// [2, 6] -> 8, 7보다 크므로 마지막 6을 빼고 candidates index++
// [2, 7] -> 9, 7보다 크므로 마지막 7을 빼고 candidates index++
// candidates를 다 돌았으므로, recurrsion 한단계 앞으로 가서 1번째 칸의 index++

// [3] -> 3
// [3, 3] -> 6
// [3, 3, 3] -> 9, 7보다 크므로 마지막 3을 빼고 candidates index++
// [3, 3, 6] -> 12, 7보다 크므로 마지막 6을 빼고 candidates index++
// [3, 3, 7] -> 13, 7보다 크므로 마지막 7을 빼고 candidates index++
// candidates를 다 돌았으므로, recurrsion 한단계 앞으로 가서 2번째 칸의 index++
// [3, 6] -> 9, 7보다 크므로 마지막 6을 빼고 candidates index++
// [3, 7] -> ...
// candidates를 다 돌았으므로, recurrsion 한단계 앞으로 가서 1번째 칸의 index++

// [6] -> 6
// [6, 6] -> 12 ...

// [7] -> 7, 만족하므로 result에 push