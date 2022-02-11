#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

// #sliding window
// #438
// s2�� s1�� ������ �����ϸ� true, �ƴϸ� false
// s1 = "ab", s2 = "eidbaooo"�̸�, s1�� ������ ba�� s2�� substr�̹Ƿ�, true
// 1. brute force s1�� ������ ���� ���Ѵ�����, s2�� substr���� Ȯ��
// 2. sliding window. �����̳ʿ� �����ϸ鼭 Ȯ��

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
            // sliding window��, s1�� size��ŭ�� window�� s2���� ���������鼭 üũ�Ѵ�.
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