#pragma once
#include <string>
#include <unordered_map>

// hash_map 사용.
// 알파벳은 26개니까 컨테이너 사이즈 fix 가능

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