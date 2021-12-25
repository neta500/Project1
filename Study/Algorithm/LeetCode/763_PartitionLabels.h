#pragma once
#include <vector>
#include <string>
#include <unordered_map>

// #greedy #hash

class Solution {
public:
    std::vector<int> partitionLabels(std::string s) {
        // ���ĺ���, �� ���ĺ��� ���������� ������ index�� ����.
        std::unordered_map<char, int> hash_map;
        std::vector<int> partitions;

        for (int i = 0; i < s.size(); ++i)
        {
            hash_map[s[i]] = i;
        }

        int lastIndex = 0;
        int pastIndex = 0;
        // �ش� ���ĺ��� ������ �ε����� ���ö����� partition�� ��´�.
        for (int i = 0; i < s.size(); ++i)
        {            
            const int index = hash_map[s[i]];
            lastIndex = std::max(lastIndex, index);

            if (i == lastIndex)
            {
                partitions.push_back(i + 1 - pastIndex);
                pastIndex = lastIndex + 1;
            }
        }

        return partitions;
    }
};