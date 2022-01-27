#pragma once
#include <vector>
#include <string>

// ["flow", "fly", "fleet"] -> "fl"
// 첫 문자열 기준으로 하나씩 비교해도 된다.

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        
        std::string result = strs.front();

        // O(n)
        for (const std::string& str : strs)
        {
            if (str == result)
            {
                continue;
            }

	        if (str.empty())
	        {
                return "";
	        }

            // 같은데까지 index 잘라주고,
            int i = 0;
            for (i = 0; i < str.size(); ++i)
            {
	            if (result[i] != str[i])
	            {
                    break;
	            }
            }

            // 같은 인덱스까지만 substr 해준다.
            result = result.substr(0, i);
            if (result.empty())
            {
                return result;
            }
        }

        return result;
    }
};