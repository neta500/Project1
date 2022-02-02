#pragma once
#include <string>
#include <vector>
#include <unordered_map>

// #sliding window
// s = "cbaebabacd", p = "abc" -> [0(cba), 6(bac)]
// s = "abab"      , p = "ab"  -> [0(ab), 1(ba), 2(ab)]
// p의 아나그램이 시작되는 index를 s에서 찾아서 리턴.

class Solution {
public:
    std::vector<int> findAnagrams(std::string s, std::string p) {
        if (s.size() < p.size()) return std::vector<int>{};
        
        std::unordered_map<char, int> map_p;
        for (const char c : p)
        {
            map_p[c]++;
        }
        
        std::unordered_map<char, int> map_s;
        for (int i = 0; i < p.size(); ++i)
        {
            map_s[s[i]]++;
        }
        
        std::vector<int> result;

        // map_s는 ++,-- 하면서 count가 0인 char가 남아있을 수 있어서,
        // map operator==는 사용 못함. map_p를 돌면서 count를 비교 O(p)
        auto isEqual = [&]
		{
            for (const auto& [c, count] : map_p)
            {
	            if (map_s[c] != count)
	            {
                    return false;
	            }
            }

            return true;
        };

        // s를 순회하며 p의 size만큼 아나그램을 분석한다. O(s-p)
        for (int i = 0; i < s.size() - p.size() + 1; ++i)
        {
            // O(p)
            if (isEqual())
            {
                result.push_back(i);
            }

            map_s[s[i]]--;
            map_s[s[i + p.size()]]++;
        }

        // time comp = O(s-p) * O(p)
        return result;
    }

    // 아래 함수는 time limit에 걸림
    std::vector<int> findAnagrams_2(std::string s, std::string p) {
        if (s.size() < p.size()) return std::vector<int>{};

        std::unordered_map<char, int> map;
        for (const char c : p)
        {
            map[c]++;
        }

        auto isAnagramOf = [&map](const std::string& str) -> bool
        {
            auto temp = map;
            for (const char c : str)
            {
                temp[c]--;
            }

            for (const auto& [c, count] : temp)
            {
                if (count > 0)
                {
                    return false;
                }
            }

            return true;
        };

        std::vector<int> result;

        // s를 순회하며 p의 size만큼 아나그램을 분석한다.
        for (int i = 0; i < s.size() - p.size() + 1; ++i)
        {
            const std::string substr = s.substr(i, p.size());
            if (true == isAnagramOf(substr))
            {
                result.push_back(i);
            }
        }

        return result;
    }
};