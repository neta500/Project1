#pragma once
#include <string>

// kmp��°͵� �ִ�.
// std::string�� find�� contains�� ��� ����������

class Solution {
public:
    int strStr(std::string haystack, std::string needle) {

        if (haystack.size() < needle.size())
        {
            return -1;
        }

        if (haystack == "" && needle == "")
        {
            return 0;
        }

        // std::string::find
        return haystack.find(needle);

        // Ravin karp (rolling-hash ���)
        /*const auto needle_hash = std::hash<std::string>()(needle);

        for (auto i = 0; i < haystack.size(); ++i)
        {
            const std::string substr = haystack.substr(i, needle.size());
            if (needle_hash == std::hash<std::string>()(substr))
            {
                return i;
            }
        }

        return -1;*/
    }
};