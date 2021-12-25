#pragma once
#include <string>
#include <stack>

class Solution {
public:
    std::string decodeString(std::string s) {
        std::stack<char> stack;

        for (const char c : s)
        {            
            // 그냥 넣어도 되는 경우: 비었을때, top이 [, 문자인 경우
            if (stack.empty() || stack.top() == '[' || std::isalpha(c))
            {
                stack.emplace(c);
            }
            else
            {
                const char top = stack.top();         
                // ] 인경우


                // 숫자인 경우
            }
        }
    }
};