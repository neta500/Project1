#pragma once
#include <string>
#include <stack>

// string���� k���� ���ڸ� ������, ���� ���� ���� �����
// "1432219", k = 3 -> "432"�� ������ ���� ���� ���� "1219"
// stack�� ���

class Solution {
public:
    std::string removeKdigits(std::string num, int k) {
        if (num.size() <= k)
        {
            return "0";
        }

        if (k == 0)
        {
            return num;
        }

        std::string result;
        std::stack<int> stack;
        stack.push(num[0]);

        for (int i = 1; i < num.size(); ++i)
        {
	        while (k > 0 && stack.empty() == false && num[i] < stack.top())
	        {
                --k;
                stack.pop();
	        }

            stack.push(num[i]);

            if (stack.size() == 1 && num[i] == '0')
            {
                stack.pop();
            }            
        }

        while (k > 0 && stack.empty() == false)
        {
            --k;
            stack.pop();
        }

        while (stack.empty() == false)
        {
            result.push_back(stack.top());
            stack.pop();
        }

        std::reverse(result.begin(), result.end());

        if (result.empty())
        {
            return "0";
        }

        return result;
    }
};