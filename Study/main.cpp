#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/LeetCode/62_UniquePaths.h"

int main()
{
    Solution solution;
    std::vector<int> vec{ 2,3,1,1,4 };
    const auto result = solution.uniquePaths_gamma(3,7);

    int a = 5;
    a /= 10;

    return 0;
}
