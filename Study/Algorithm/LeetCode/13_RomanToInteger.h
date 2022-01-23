#pragma once
#include <string>
#include <unordered_map>

// I - 1
// V - 5
// X - 10
// L - 50
// C - 100
// D - 500
// M - 1000
// III = 3, LVIII = 58(L+V+III), MCMXCIV = 1994(M+CM+XC+IV)

class Solution {
public:
    int romanToInt(std::string s) {
        std::unordered_map<char, int> map
    	{
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
    	};


        int num = 0;
        int size = s.size();

        for (int i = 0; i < size; ++i)
        {
	        if (i < size - 1 && map[s[i]] < map[s[i+1]])
	        {
                num -= map[s[i]];
	        }
            else
            {
                num += map[s[i]];
            }
        }

        return num;
    }
};