#pragma once
#include <vector>
#include <string>
#include <stack>

// 소괄호 n개로, 열고 닫는게 올바른 모든 조합 구하기
// n=3, ["((()))", "(()())", "(())()", "()(())", "()()()"]
// 난 모르겠다이거..

class Solution {
	std::vector<std::string> result;
public:
    std::vector<std::string> generateParenthesis(int n) {
        add("", n, 0);
        return result;
    }

    void add(std::string str, int left, int right)
    {
	    if (left == 0 && right == 0)
	    {
            result.push_back(str);
            return;
	    }

        if (right > 0)
        {
            add(str + ")", left, right - 1);            
        }
        if (left > 0)
        {
            add(str + "(", left - 1, right + 1);
        }
    }
};