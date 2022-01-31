#pragma once
#include <string>

// 마지막 단어의 길이 구하기
// "hello world" -> 5(world)
// 어차피 앞의 단어들은 관심이 없기때문에, 뒤에서부터 구한다.

class Solution {
public:
    int lengthOfLastWord(std::string s) {
        int length = 0;
        bool charDiscovered = false;

        for (int i = s.length() - 1; i >= 0; --i)
        {
	        if (s[i] == ' ' && charDiscovered == true)
	        {
                break;
	        }

			if (s[i] != ' ')
			{
				charDiscovered = true;
				length++;
			}
		}

        return length;
    }
};
