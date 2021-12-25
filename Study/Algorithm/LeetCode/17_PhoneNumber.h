#pragma once
#include <vector>
#include <string>

class Solution {
    std::vector<std::string> map =
    { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

    std::vector<std::string> result{""};

public:
    std::vector<std::string> letterCombinations(std::string digits) {
        if (digits == "") return std::vector<std::string>{};
        
        for (const auto digit : digits)
        {
            std::vector<std::string> extentCombination;
            for (const auto& currentCombination : result)
            {
                for (const auto newChar : map[digit - '2'])
                {
                    extentCombination.emplace_back(currentCombination + newChar);
                }
            }
            result = std::move(extentCombination);
        }

        return result;
    }
};