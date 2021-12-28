#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include "Algorithm/LeetCode/26_RemoveDuplicatesefromSortedArray.h"


int main()
{
    Solution solution;
    std::vector<int> vec{ 0,0,1,1,2 };
    const auto result = solution.removeDuplicates(vec);
    return 0;
}
