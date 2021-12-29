#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include "Algorithm/LeetCode/350_IntersectionofTwoArraysll.h"


int main()
{
    Solution solution;
    std::vector<int> vec{ 4,9,5 };
    std::vector<int> vec2{ 9,4,9,8,4 };
    const auto result = solution.intersect(vec, vec2);
    return 0;
}
