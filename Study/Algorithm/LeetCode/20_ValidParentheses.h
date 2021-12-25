#pragma once
#include <string>
#include <stack>

class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> stack;

        for (const char c : s)
        {
            if (stack.empty())
            {
                if (c == '}' || c == ']' || c == ')')
                {
                    return false;
                }
                else
                {
                    stack.emplace(c);
                }
            }
            else
            {
                // 여는건 무조건 넣어
                if (c == '{' || c == '[' || c == '(')
                {
                    stack.emplace(c);
                }
                else
                {
                    const auto top = stack.top();
                    // 닫는괄호면 top이랑 비교해서, 맞으면 top을 pop
                    if (c == '}')
                    {
                        if (top == '{')
                        {
                            stack.pop();
                            continue;
                        }
                    }
                    else if (c == ')')
                    {
                        if (top == '(')
                        {
                            stack.pop();
                            continue;
                        }
                    }
                    else // (c == ']'
                    {
                        if (top == '[')
                        {
                            stack.pop();
                            continue;
                        }
                    }

                    // pop 못했으면 실패임
                    return false;
                }
            }
        }

        // 스택에 남은게 있으면 false
        if (false == stack.empty())
        {
            return false;
        }

        return true;
    }
};