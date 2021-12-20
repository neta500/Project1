#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include "Algorithm/LeetCode/416_PartitionEqualSubsetSum.h"

int main()
{    
    Solution solution;
    
    std::vector<int> vec{ 1,5, 11, 4 };
    const auto result = solution.canPartition(vec);
    return 0;
}
