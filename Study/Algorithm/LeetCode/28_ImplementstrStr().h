#pragma once
#include <string>

// kmp라는것도 있다.
// std::string의 find와 contains는 어떻게 구현했을까

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

        // Ravin karp (rolling-hash 기법)
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