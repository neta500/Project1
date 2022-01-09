#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/LeetCode/22_GenerateParentheses.h"

int main()
{
    Solution solution;
    std::vector<int> vec{-1,0,1,2,-1,-4};
    const auto result = solution.generateParenthesis(3);

    return 0;
}
