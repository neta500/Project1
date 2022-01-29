#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/Sorting.h"
#include "Algorithm/Graph.h"
#include "Algorithm/LeetCode/14_LongestCommonPrefix.h"

using namespace sort;
using namespace graph;

int main()
{
    Solution solution;
    std::vector<int> vec{ 7,0,1,4,3,2,0 };
    std::vector<std::string> strVec{ "flow", "fly", "fleet" };
    const auto result = solution.longestCommonPrefix(strVec);
    QuickSort(vec, 0, vec.size()-1);

    bfs();
    dijkstra();

    return 0;
}

