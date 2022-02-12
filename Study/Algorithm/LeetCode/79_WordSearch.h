#pragma once
#include <vector>
#include <string>

// #graph #dfs
// m x n grid에서 인접한 cell로, word가 존재하는지 여부
// 각 cell에서 시작해서, dfs로 체크한다.

class Solution {
public:
    bool dfs(std::vector<std::vector<char>>& board, int i, int j, std::string& word)
    {
	    if (word.empty())
	    {
			return true;
	    }

		// i, j 가 board 크기를 벗어나거나, 시작 cell이 word[0]와 다른경우 실패
		if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()
			|| board[i][j] != word[0])
		{
			return false;
		}

		// 여기까지 왔으면 word가 일치한다는 소리.
		char c = board[i][j];

		// seen cell은 표시해놓는다.
		board[i][j] = '*';
		std::string str = word.substr(1);

		// 인접한 cell에 대해 dfs를 수행한다.
		bool result = 
			dfs(board, i - 1, j, str) ||
			dfs(board, i + 1, j, str) ||
			dfs(board, i, j - 1, str) ||
			dfs(board, i, j + 1, str);

		// 인접한 cell에 대해 dfs를 다 수행했으면, seen cell을 다시 원상복귀시킨다.
		// (exist 함수에서 다음 for loop를 수행하기 위함)
		board[i][j] = c;

		return result;
    }

    bool exist(std::vector<std::vector<char>>& board, std::string word) {
		// board를 순회하면서, 각 cell에서 dfs를 수행하며 체크한다.
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