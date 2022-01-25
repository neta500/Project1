#pragma once
#include <string>

// 1. � ���ڿ��� Palindrome�̴� -> �� ���ڿ��� ���� ���ڿ��� Palindrome�̴ٸ� �̿��� dp����
// P(i,j) = P(i+1, j-1) && �翷���ڰ� ����

// 2. ��� ���ڿ������� �翷���� index�� �÷�����, Palindrome���� üũ�Ѵ�. O(n^2)
// ���⼭, �� ���ڿ��� Ȧ���̸� ��� ���ڰ� �Ѱ�, ¦���̸� ��� ���ڰ� �ΰ��� �����Ѵ�.

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

            // ���ӵ� ���ڿ��� ������ ��� ó�� ("cbbd"�� ��� left�� b(1), right�� b(2)�� ��)
            while (right < size - 1 && s[right] == s[right + 1])
            {
                right++;
            }

            i = right + 1;

            // left�� ��������, right�� ���������� �������� palindrome�� �˻��Ѵ�.
            while (right < size - 1 && left > 0 && s[right + 1] == s[left - 1])
            {
                right++;
                left--;
            }

            // palindrome�� �������� max���� �� �� ó��
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