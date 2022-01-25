#pragma once
#include <string>

// 1. 어떤 문자열이 Palindrome이다 -> 그 문자열의 내부 문자열도 Palindrome이다를 이용한 dp문제
// P(i,j) = P(i+1, j-1) && 양옆문자가 같음

// 2. 가운데 문자에서부터 양옆으로 index를 늘려가며, Palindrome인지 체크한다. O(n^2)
// 여기서, 총 문자열이 홀수이면 가운데 문자가 한개, 짝수이면 가운데 문자가 두개로 시작한다.

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        if (s.size() < 2) return s;

        const int size = s.size();
        int start = 0; int end = 0;

        int i = 0;

        while (i < size)
        {
            int left = i; int right = i;

            // 연속된 문자열이 나오는 경우 처리 ("cbbd"의 경우 left가 b(1), right가 b(2)가 됨)
            while (right < size - 1 && s[right] == s[right + 1])
            {
                right++;
            }

            i = right + 1;

            // left는 왼쪽으로, right는 오른쪽으로 넓혀가며 palindrome을 검사한다.
            while (right < size - 1 && left > 0 && s[right + 1] == s[left - 1])
            {
                right++;
                left--;
            }

            // palindrome이 구해지면 max값을 비교 후 처리
            int length = right - left + 1;
            if (length > end)
            {
                end = length;
                start = left;
            }
        }

        return s.substr(start, end);
    }
    
};