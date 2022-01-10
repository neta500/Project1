#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/LeetCode/33_SearchinRotatedSortedArray.h"

int main()
{
    Solution solution;
    std::vector<int> vec{4,5,6,7,0,1,2};
    const auto result = solution.search(vec, 0);

    return 0;
}
