#pragma once
#include <string>

class Solution {
public:
    bool isPalindrome(std::string s) {
        int leftIndex = 0;
        int rightIndex = s.size() - 1;

        while (leftIndex < rightIndex)
        {
            bool leftIndexUpdated = false;
            bool rightIndexUpdated = false;

            auto left = s.at(leftIndex);
            auto right = s.at(rightIndex);

            if (0 == std::isalnum(left))
            {
                leftIndex++; 
                leftIndexUpdated = true;
            }

            if (0 == std::isalnum(right))
            {
                rightIndex--;
                rightIndexUpdated = true;
            }

            if (leftIndexUpdated == false && rightIndexUpdated == false)
            {
                if (std::tolower(left) != std::tolower(right))
                {
                    return false;
                }
                else
                {
                    if (false == rightIndexUpdated)
                    {
                        rightIndex--;
                    }

                    if (false == leftIndexUpdated)
                    {
                        leftIndex++;
                    }
                }
            }            
        }

        return true;
    }
};