#pragma once
#include <string>

// left, right 2pointer�� �������鼭 üũ.

class Solution {
public:
    bool isPalindrome(std::string s) {
        int leftIndex = 0;
        int rightIndex = s.size() - 1;

        while (leftIndex < rightIndex)
        {
            auto left = s.at(leftIndex);
            auto right = s.at(rightIndex);

            // ���ڳ� ���ڰ� �ƴϸ� �н�
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