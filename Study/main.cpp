#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/Sorting/Sorting.h"
#include "Algorithm/LeetCode/13_RomanToInteger.h"

int main()
{
    Solution solution;
    std::vector<int> vec{ 7,5,1,4,3,2,9 };
    const auto result = solution.romanToInt("MCMXCIV");
    QuickSort(vec, 0, vec.size()-1);

    

    return 0;
}
