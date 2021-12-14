#pragma warning(disable:4819)
#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include "Algorithm/LeetCode/49_GroupAnagrams.h"

int main()
{    
    std::vector<std::string> strs{ "eat", "tea", "tan", "ate", "nat", "bat" };

    Solution solution;
    const auto result = solution.groupAnagrams_bycounting(strs);
    return 0;
}