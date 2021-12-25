#pragma once
#include <vector>
#include <string>

// ���ӵǴ� ���ĺ� ����� (�ּ����� cost��)

class Solution {
public:
    int minCost(std::string colors, std::vector<int>& neededTime) {
        int totalCost = 0;

        for (int i = 0; i < colors.size(); ++i)
        {
            if (colors[i] == colors[i + 1])
            {
                totalCost += std::min(neededTime[i], neededTime[i + 1]);

                // ���� aaa�� cost�� 4 2 7 ������� cost�� 4, 2�� a�� �����Ѵ�
                // �׷��� 4,2 �� �� 2,7�� ���Ҷ� 4�� �������ϱ⶧����
                // 4,2 �� �� 2 �ڸ��� 4�� ������Ʈ���༭ 4�� 7�� ���ϰ� �ϸ��.
                // 2�� �̹� 4,2 �񱳿��� cost�� �߰��Ǿ����ϱ� ���̻� �ʿ���� ������
                neededTime[i + 1] = std::max(neededTime[i], neededTime[i + 1]);
            }
        }

        return totalCost;
    }
};