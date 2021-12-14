#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>

// 1. str들을 정렬한 후, hash_map에 집어넣는다.
// 2. str들의 알파벳 개수를 센 후, hash_map에 집어넣는다.
// key를 뭘로 쓰냐가 핵심

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams_bycounting(std::vector<std::string>& strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> map;
        std::map<char, int> countMap;

        auto getCountKey = [&countMap](const std::string& str) -> std::string
        {
            for (const auto& c : str)
            {
                if (const auto found = countMap.find(c); found != countMap.cend())
                {
                    found->second++;
                }
                else
                {
                    countMap.emplace(c, 1);
                }
            }

            std::string key;
            for (const auto& [c, count] : countMap)
            {
                if (count > 0)
                {
                    key.append(std::string{ c });
                    key.append(std::to_string(count));
                }
            }

            return key;
        };

        for (const std::string& str : strs)
        {
            const auto key = getCountKey(str);
            
            if (const auto found = map.find(key); found != map.cend())
            {
                found->second.emplace_back(str);
            }
            else
            {
                map.emplace(key, std::vector<std::string>{str});
            }

            countMap.clear();
        }

        std::vector<std::vector<std::string>> vec{};

        for (const auto& [key, str] : map)
        {
            vec.emplace_back(str);
        }

        return vec;
    }

    std::vector<std::vector<std::string>> groupAnagrams_bysorting(std::vector<std::string>& strs) {

        std::unordered_map<std::string, std::vector<std::string>> map;

        for (const std::string& str : strs)
        {
            std::string sorted_str = str;
            std::sort(sorted_str.begin(), sorted_str.end());
            
            if (const auto found = map.find(sorted_str); found != map.cend())
            {
                found->second.emplace_back(str);
            }
            else
            {
                map.emplace(sorted_str, std::vector<std::string>{str});
            }
        }

        std::vector<std::vector<std::string>> vec{};

        for (const auto& [sorted_str, str] : map)
        {
            vec.emplace_back(str);
        }

        return vec;
    }
};