#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>

// 1. str���� ������ ��, hash_map�� ����ִ´�.
// 2. str���� ���ĺ� ������ �� ��, hash_map�� ����ִ´�.
// key�� ���� ���İ� �ٽ�

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams_bycounting(std::vector<std::string>& strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> map;
        std::map<char, int> countMap; // �� string�� ����, ������ ������ ����.

        // string�� ����, ���ڼ��� countMap�� �����ϴ� �Լ�.
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

            // �� �� key�� map ������ �����̴�. �������
            // a3b2c1 �̷���. (aaabbbc, aabbabc ... ���� anagram set)
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

            // key (a3b2c1)�� �����Ѵ�. (anagram�̴ϱ� �翬�� ��ġ�°� ����)
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

        // ��������� vector�� �������ش�.
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