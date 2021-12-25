#pragma once
#include <vector>
#include <string>

// 1. two pointers swap O(n)

class Solution {
public:
    void reverseString(std::vector<char>& s) {
        std::reverse(s.begin(), s.end());
    }
};