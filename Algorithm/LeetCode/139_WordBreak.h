#pragma once
#include <string>
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        std::unordered_set<std::string> dic;
        for (const auto& str : wordDict)
        {
            dic.emplace(str);
        }

        std::vector<bool> possible(s.length(), false);

        // dp
        for (int i = s.length() - 1; i >= 0; --i)
        {
            // 문자열의 우측부터 하나씩 <- 해가며, 그 단어가 dic에 있는지 체크한다.
            // 있으면 possible의 해당 index를 true로 체크해주고, 다음번 계산에 이용한다.
            std::string right = "";
            
            for (int j = i; j < s.length(); ++j)
            {
                right += s[j];
                if (dic.contains(right) && (j == s.length() - 1 || possible[j + 1]))
                {
                    possible[i] = 1;
                    break;
                }
            }
        }

        return possible[0];
    }
};