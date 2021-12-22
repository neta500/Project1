#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include "Algorithm/LeetCode/51_N-Queens.h"

int main()
{    
    Solution solution;
    std::vector<int> nums{ 2,3,6,7 };
    const auto result = solution.solveNQueens(4);
    return 0;
}
