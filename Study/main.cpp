#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/LeetCode/55_JumpGame.h"

int main()
{
    Solution solution;
    std::vector<int> vec{ 2,3,1,1,4 };
    const auto result = solution.canJump(vec);

    return 0;
}
