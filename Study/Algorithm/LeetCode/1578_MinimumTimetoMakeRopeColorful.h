#pragma once
#include <vector>
#include <string>

// 연속되는 알파벳 지우기 (최소한의 cost로)

class Solution {
public:
    int minCost(std::string colors, std::vector<int>& neededTime) {
        int totalCost = 0;

        for (int i = 0; i < colors.size(); ++i)
        {
            if (colors[i] == colors[i + 1])
            {
                totalCost += std::min(neededTime[i], neededTime[i + 1]);

                // 만약 aaa의 cost가 4 2 7 순서라면 cost가 4, 2인 a를 골라야한다
                // 그런데 4,2 비교 후 2,7을 비교할때 4를 골라줘야하기때문에
                // 4,2 비교 후 2 자리를 4로 업데이트해줘서 4와 7을 비교하게 하면됨.
                // 2는 이미 4,2 비교에서 cost에 추가되었으니까 더이상 필요없는 데이터
                neededTime[i + 1] = std::max(neededTime[i], neededTime[i + 1]);
            }
        }

        return totalCost;
    }
};