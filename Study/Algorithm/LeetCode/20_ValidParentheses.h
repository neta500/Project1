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
                // ���°� ������ �־�
                if (c == '{' || c == '[' || c == '(')
                {
                    stack.emplace(c);
                }
                else
                {
                    const auto top = stack.top();
                    // �ݴ°�ȣ�� top�̶� ���ؼ�, ������ top�� pop
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

                    // pop �������� ������
                    return false;
                }
            }
        }

        // ���ÿ� ������ ������ false
        if (false == stack.empty())
        {
            return false;
        }

        return true;
    }
};