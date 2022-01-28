#pragma once
#include <string>
#include <unordered_map>

// 중복되지 않은 문자들로 이루어진 가장 긴 substr의 길이 구하기
// "abcabcbb" -> "abc"가 가장 긴 substr이므로, 3
// string에 longest? 바로 stack..이 아니고 중복되지 않는 문자니까 카운트를 해야함.

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        // 문자와 index를 저장한다.
        std::unordered_map<char, int> map;
        int startIndex = -1;
        int maxLength = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            // 중복인경우 
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