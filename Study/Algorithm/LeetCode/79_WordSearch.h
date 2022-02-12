#pragma once
#include <vector>
#include <string>

// #graph #dfs
// m x n grid���� ������ cell��, word�� �����ϴ��� ����
// �� cell���� �����ؼ�, dfs�� üũ�Ѵ�.

class Solution {
public:
    bool dfs(std::vector<std::vector<char>>& board, int i, int j, std::string& word)
    {
	    if (word.empty())
	    {
			return true;
	    }

		// i, j �� board ũ�⸦ ����ų�, ���� cell�� word[0]�� �ٸ���� ����
		if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()
			|| board[i][j] != word[0])
		{
			return false;
		}

		// ������� ������ word�� ��ġ�Ѵٴ� �Ҹ�.
		char c = board[i][j];

		// seen cell�� ǥ���س��´�.
		board[i][j] = '*';
		std::string str = word.substr(1);

		// ������ cell�� ���� dfs�� �����Ѵ�.
		bool result = 
			dfs(board, i - 1, j, str) ||
			dfs(board, i + 1, j, str) ||
			dfs(board, i, j - 1, str) ||
			dfs(board, i, j + 1, str);

		// ������ cell�� ���� dfs�� �� ����������, seen cell�� �ٽ� ���󺹱ͽ�Ų��.
		// (exist �Լ����� ���� for loop�� �����ϱ� ����)
		board[i][j] = c;

		return result;
    }

    bool exist(std::vector<std::vector<char>>& board, std::string word) {
		// board�� ��ȸ�ϸ鼭, �� cell���� dfs�� �����ϸ� üũ�Ѵ�.
        for (int i = 0; i < board.size(); ++i)
        {
	        for (int j = 0; j < board[0].size(); ++j)
	        {
		        if (dfs(board, i, j, word))
		        {
					return true;
		        }
	        }
        }

		return false;
    }
};