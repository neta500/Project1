#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/LeetCode/387_FirstUniqueCahracterinaString.h"


int main()
{
    Solution solution;
    std::vector<int> vec{1,2,3,4,5,6,7};
    const auto result = solution.firstUniqChar("leetcode");

    std::scoped_lock lock;

    return 0;
}
