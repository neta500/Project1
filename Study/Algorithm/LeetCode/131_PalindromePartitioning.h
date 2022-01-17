#pragma once
#include <vector>
#include <string>

// #backtracking
// string을 palindrome인 substr들로 쪼개기.
// "aab" -> [a,a,b], [aa,b]

class Solution {
public:
    std::vector<std::vector<std::string>> result;

    bool isPalindrome(std::string& s, int low, int high)
    {
	    while (low < high)
	    {
            if (s[low++] != s[high--]) return false;            
	    }

        return true;
    }

    void dfs(std::string& s, int start, std::vector<std::string>& currentList)
    {
	    if (start >= s.length())
	    {
            result.push_back(currentList);
	    }

        for (int end = start; end < s.length(); ++end)
        {
	        if (isPalindrome(s, start, end))
	        {
                currentList.push_back(s.substr(start, end - start + 1));
                dfs(s, end + 1, currentList);
                currentList.pop_back();
	        }
        }
    }

    std::vector<std::vector<std::string>> partition(std::string s) {
        std::vector<std::string> currentList;
        dfs(s, 0, currentList);
        return result;
    }
};