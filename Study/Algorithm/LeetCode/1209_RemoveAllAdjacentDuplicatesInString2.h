#pragma once
#include <string>
#include <stack>
#include <unordered_map>

class Solution {
public:
    std::string removeDuplicates(std::string s, int k) {
        std::stack<std::pair<char, int>> stack;

        for (const char c : s)
        {
            if (stack.empty() || c != stack.top().first)
            {
                stack.emplace(c, 1);
            }
            else
            {
                stack.top().second++;
                if (stack.top().second == k)
                {
                    stack.pop();
                }
            }
        }

        std::string str;
        while (false == stack.empty())
        {
            str.append(std::string( stack.top().second, stack.top().first ));
            stack.pop();
        }
        std::reverse(str.begin(), str.end());

        return str;
    }
};