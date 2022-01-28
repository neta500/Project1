#pragma once
#include <string>
#include <unordered_map>

// �ߺ����� ���� ���ڵ�� �̷���� ���� �� substr�� ���� ���ϱ�
// "abcabcbb" -> "abc"�� ���� �� substr�̹Ƿ�, 3
// string�� longest? �ٷ� stack..�� �ƴϰ� �ߺ����� �ʴ� ���ڴϱ� ī��Ʈ�� �ؾ���.

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        // ���ڿ� index�� �����Ѵ�.
        std::unordered_map<char, int> map;
        int startIndex = -1;
        int maxLength = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            // �ߺ��ΰ�� 
	        if (map.contains(s[i]))
	        {
                startIndex = std::max(startIndex, map[s[i]]);
	        }

            map[s[i]] = i;
            maxLength = std::max(maxLength, i - startIndex);
        }

        return maxLength;
    }
};