#pragma once
#include <vector>

// [1,2,3] -> [1,2,4]
// [9] -> [1, 0]

class Solution {
public:
    std::vector<int> plusOne(std::vector<int>& digits) {
        for (int i = digits.size()-1; i >= 0; --i)
        {
            if (digits[i] == 9)
            {
                digits[i] = 0;
            }
            else
            {
                digits[i]++;
                return digits;
            }
        }

        digits.push_back(0);
        digits[0] = 1;
        return digits;
    }
};