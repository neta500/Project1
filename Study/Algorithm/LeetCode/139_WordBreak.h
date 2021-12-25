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
            // ���ڿ��� �������� �ϳ��� <- �ذ���, �� �ܾ dic�� �ִ��� üũ�Ѵ�.
            // ������ possible�� �ش� index�� true�� üũ���ְ�, ������ ��꿡 �̿��Ѵ�.
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