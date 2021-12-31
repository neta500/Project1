#pragma once
#include <string>
#include <unordered_map>

// anagram 체크는 각 char의 숫자를 세서, 같으면 true
// valid palindrome과 마찬가지로, hash_map의 크기를 알파벳 26의 array으로 변경 가능

class Solution {
public:
    bool isAnagram(std::string s, std::string t) {
        std::unordered_map<char, int> map;

        // 한쪽은 ++
        for (const char c : s)
        {
            map[c]++;
        }

        // 다른쪽은 --
        for (const char c : t)
        {
            map[c]--;
        }

        // 0이 아니면 false
        for (const auto& [c, count] : map)
        {
            if (count != 0)
            {
                return false;
            }
        }

        return true;
    }
};