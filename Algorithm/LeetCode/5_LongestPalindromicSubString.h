#pragma once
#include <string>

// 1. � ���ڿ��� Palindrome�̴� -> �� ���ڿ��� ���� ���ڿ��� Palindrome�̴ٸ� �̿��� dp����
// P(i,j) = P(i+1, j-1) && �翷���ڰ� ����

// 2. ��� ���ڿ������� �翷���� index�� �÷�����, Palindrome���� üũ�Ѵ�.
// ���⼭, �� ���ڿ��� Ȧ���̸� ��� ���ڰ� �Ѱ�, ¦���̸� ��� ���ڰ� �ΰ��� �����Ѵ�.

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        int ans = 0, index = -1, len = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            // �� ���̰� ¦��
            len = 2 * lengthOfPalindrome(s, i, i + 1);
            if (ans < len)
            {
                ans = len;
                index = i - len / 2 + 1;
            }

            // �� ���̰� Ȧ��
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