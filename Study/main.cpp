#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/LeetCode/198_HouseRobber.h"

int main()
{
    Solution solution;
    std::vector<int> vec{2,7,9,3,1};
    const auto result = solution.rob(vec);

    return 0;
}
