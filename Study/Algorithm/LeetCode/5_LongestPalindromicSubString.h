#pragma once
#include <string>

// 1. 어떤 문자열이 Palindrome이다 -> 그 문자열의 내부 문자열도 Palindrome이다를 이용한 dp문제
// P(i,j) = P(i+1, j-1) && 양옆문자가 같음

// 2. 가운데 문자에서부터 양옆으로 index를 늘려가며, Palindrome인지 체크한다.
// 여기서, 총 문자열이 홀수이면 가운데 문자가 한개, 짝수이면 가운데 문자가 두개로 시작한다.

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        int ans = 0, index = -1, len = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            // 총 길이가 짝수
            len = 2 * lengthOfPalindrome(s, i, i + 1);
            if (ans < len)
            {
                ans = len;
                index = i - len / 2 + 1;
            }

            // 총 길이가 홀수
            len = 2 * lengthOfPalindrome(s, i - 1, i + 1) + 1;
            if (ans < len)
            {
                ans = len;
                index = i - len / 2;
            }
        }

        return std::string(s.begin() + index, s.begin() + index + ans);
    }

private:
    int lengthOfPalindrome(std::string s, int left, int right)
    {
        int length = 0;
        for (auto i = left, j = right; j < s.size() && i >= 0; --i, ++j)
        {
            if (s.at(i) != s.at(j))
            {
                return length;
            }

            ++length;
        }

        return length;
    }
};