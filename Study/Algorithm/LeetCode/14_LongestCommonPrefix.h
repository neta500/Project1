#pragma once
#include <vector>
#include <string>

// ["flow", "fly", "fleet"] -> "fl"
// 첫 문자열 기준으로 하나씩 비교해도 된다.

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        std::string result = strs[0];
        for (const std::string& str : strs)
        {
	        if (str.empty())
	        {
                return "";
	        }

            int i = 0;
            for (i = 0; i < str.size(); ++i)
            {
	            if (result[i] != str[i])
	            {
                    break;
	            }
            }

            result = result.substr(0, i);
            if (result.empty())
            {
                return result;
            }
        }

        return result;
    }
};