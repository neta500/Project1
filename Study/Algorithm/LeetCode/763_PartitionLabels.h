#pragma once
#include <vector>
#include <string>
#include <unordered_map>

// #greedy #hash

class Solution {
public:
    std::vector<int> partitionLabels(std::string s) {
        // 알파벳과, 그 알파벳이 마지막으로 나오는 index를 저장.
        std::unordered_map<char, int> hash_map;
        std::vector<int> partitions;

        for (int i = 0; i < s.size(); ++i)
        {
            hash_map[s[i]] = i;
        }

        int lastIndex = 0;
        int pastIndex = 0;
        // 해당 알파벳의 마지막 인덱스가 나올때까지 partition을 잡는다.
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