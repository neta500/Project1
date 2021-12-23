#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include "Algorithm/LeetCode/763_PartitionLabels.h"

int main()
{    
    Solution solution;
    //std::vector<int> nums{ 1,1,1,2,2,3 };
    //std::vector<std::vector<int>> vec{ {1,2}, {2,3}, {3,4}, {1,3} };
    std::string s("eaaaabaaec");

    const auto result = solution.partitionLabels(s);
    return 0;
}
