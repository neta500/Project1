#pragma once
#include <string>
#include <unordered_map>

// anagram üũ�� �� char�� ���ڸ� ����, ������ true
// valid palindrome�� ����������, hash_map�� ũ�⸦ ���ĺ� 26�� array���� ���� ����

class Solution {
public:
    bool isAnagram(std::string s, std::string t) {
        std::unordered_map<char, int> map;

        // ������ ++
        for (const char c : s)
        {
            map[c]++;
        }

        // �ٸ����� --
        for (const char c : t)
        {
            map[c]--;
        }

        // 0�� �ƴϸ� false
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