#pragma once
#include <vector>
#include <string>

// ["flow", "fly", "fleet"] -> "fl"
// ù ���ڿ� �������� �ϳ��� ���ص� �ȴ�.

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