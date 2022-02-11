#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

// #sliding window
// #438
// s2가 s1의 순열을 포함하면 true, 아니면 false
// s1 = "ab", s2 = "eidbaooo"이면, s1의 순열인 ba가 s2의 substr이므로, true
// 1. brute force s1의 순열을 전부 구한다음에, s2의 substr인지 확인
// 2. sliding window. 컨테이너에 저장하면서 확인

class Solution {
public:
    bool checkInclusion(std::string s1, std::string s2)
    {
        std::vector<int> s1map(26, 0);
        std::vector<int> s2map(26, 0);

        for (int i = 0; i < s1.size(); ++i)
        {
            s1map[s1[i] - 'a']++;
        }

        for (int i = 0; i < s2.size(); ++i)
        {
            // sliding window로, s1의 size만큼의 window를 s2에서 움직여가면서 체크한다.
            s2map[s2[i] - 'a']++;
            if (i >= s1.size() - 1)
            {
	            if (s1map == s2map)
	            {
                    return true;
	            }

                s2map[s2[i - s1.size() + 1] - 'a']--;
            }
        }

        return false;
    }

    bool checkInclusion_bruteforce(std::string s1, std::string s2) {
        std::vector<std::string> vec;

        do
        {
            vec.push_back(s1);
        } while (std::next_permutation(s1.begin(), s1.end()));

        for (const std::string& str : vec)
        {
	        if (std::string::npos != s2.find(str))
	        {
                return true;
	        }
        }

        return false;
    }
};