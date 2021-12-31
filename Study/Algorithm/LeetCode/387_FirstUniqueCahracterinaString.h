#pragma once
#include <string>
#include <unordered_map>

// hash_map ���.
// ���ĺ��� 26���ϱ� �����̳� ������ fix ����

class Solution {
public:
    int firstUniqChar(std::string s){
        std::unordered_map<char, int> map; // index, count
        for (const char c : s)
        {
            map[c]++;
        }

        for (int i = 0; i < s.size(); ++i)
        {
            if (map[s[i]] == 1)
            {
                return i;
            }
        }

        return -1;
    }
};