#pragma once
#include <string>

// left, right 2pointer로 좁혀오면서 체크.

class Solution {
public:
    bool isPalindrome(std::string s) {
        int leftIndex = 0;
        int rightIndex = s.size() - 1;

        while (leftIndex < rightIndex)
        {
            auto left = s.at(leftIndex);
            auto right = s.at(rightIndex);

            // 문자나 숫자가 아니면 패스
            if (0 == std::isalnum(left))
            {
                leftIndex++; 
            }
            else if (0 == std::isalnum(right))
            {
                rightIndex--;
            }
            else
            {
                if (std::tolower(left) != std::tolower(right))
                {
                    return false;
                }

                leftIndex++;
                rightIndex--;
            }   
        }

        return true;
    }
};