#pragma once
#include <string>

// ������ �ܾ��� ���� ���ϱ�
// "hello world" -> 5(world)
// ������ ���� �ܾ���� ������ ���⶧����, �ڿ������� ���Ѵ�.

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
