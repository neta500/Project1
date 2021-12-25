#pragma once
#include <string>
#include <stack>

class Solution {
public:
    std::string decodeString(std::string s) {
        std::stack<char> stack;

        for (const char c : s)
        {            
            // �׳� �־ �Ǵ� ���: �������, top�� [, ������ ���
            if (stack.empty() || stack.top() == '[' || std::isalpha(c))
            {
                stack.emplace(c);
            }
            else
            {
                const char top = stack.top();         
                // ] �ΰ��


                // ������ ���
            }
        }
    }
};