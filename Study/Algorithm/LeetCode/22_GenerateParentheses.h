#pragma once
#include <vector>
#include <string>
#include <stack>

// �Ұ�ȣ n����, ���� �ݴ°� �ùٸ� ��� ���� ���ϱ�
// n=3, ["((()))", "(()())", "(())()", "()(())", "()()()"]
// �� �𸣰ڴ��̰�..

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