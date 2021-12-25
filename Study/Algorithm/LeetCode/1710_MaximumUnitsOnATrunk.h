#pragma once
#include <vector>
#include <algorithm>

// GREEDY

class Solution {
public:
    int maximumUnits(std::vector<std::vector<int>>& boxTypes, int truckSize) {
        int num = 0;
        int size = 0;

        std::sort(boxTypes.begin(), boxTypes.end(), [](const auto& vecA, const auto& vecB)
            {
                return vecA[1] > vecB[1];
            });

        for (int i = 0; i < boxTypes.size(); ++i)
        {
            for (int j = 0; j < boxTypes[i][0]; ++j)
            {
                if (size < truckSize)
                {
                    num += boxTypes[i][1];
                    size++;
                }
            }            
        }

        return num;
    }
};