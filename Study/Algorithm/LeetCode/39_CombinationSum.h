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

// current vector ����
// [2] -> 2
// [2, 2] -> 4
// [2, 2, 2] -> 6
// [2, 2, 2, 2] -> 8, 7���� ũ�Ƿ� ������ 2�� ���� candidates index++
// [2, 2, 2, 3] -> 9, 7���� ũ�Ƿ� ������ 3�� ���� candidates index++
// [2, 2, 2, 6] -> ...
// [2, 2, 2, 7] -> ...
// candidates�� �� �������Ƿ�, recurrsion �Ѵܰ� ������ ���� 3��° ĭ�� index++
// [2, 2, 3] -> 7 �����ϹǷ� result�� push
// [2, 2, 6] -> 8, 7���� ũ�Ƿ� ������ 6�� ���� cadidates index++
// [2, 2, 7] -> 9, 7���� ũ�Ƿ� ������ 7�� ���� cadidates index++
// candidates�� �� �������Ƿ�, recurrsion �Ѵܰ� ������ ���� 2��° ĭ�� index++
// [2, 3] -> 5
// [2, 6] -> 8, 7���� ũ�Ƿ� ������ 6�� ���� candidates index++
// [2, 7] -> 9, 7���� ũ�Ƿ� ������ 7�� ���� candidates index++
// candidates�� �� �������Ƿ�, recurrsion �Ѵܰ� ������ ���� 1��° ĭ�� index++

// [3] -> 3
// [3, 3] -> 6
// [3, 3, 3] -> 9, 7���� ũ�Ƿ� ������ 3�� ���� candidates index++
// [3, 3, 6] -> 12, 7���� ũ�Ƿ� ������ 6�� ���� candidates index++
// [3, 3, 7] -> 13, 7���� ũ�Ƿ� ������ 7�� ���� candidates index++
// candidates�� �� �������Ƿ�, recurrsion �Ѵܰ� ������ ���� 2��° ĭ�� index++
// [3, 6] -> 9, 7���� ũ�Ƿ� ������ 6�� ���� candidates index++
// [3, 7] -> ...
// candidates�� �� �������Ƿ�, recurrsion �Ѵܰ� ������ ���� 1��° ĭ�� index++

// [6] -> 6
// [6, 6] -> 12 ...

// [7] -> 7, �����ϹǷ� result�� push