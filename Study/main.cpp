#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/Sorting.h"
#include "Algorithm/Graph.h"
#include "Algorithm/LeetCode/567_PermutationInString.h"

using namespace sort;
using namespace graph;

int main()
{
    Solution solution;
    std::vector<int> vec{ 1,1,1,2,2,3 };
    std::vector<std::string> strVec{ "flow", "fly", "fleet" };
    const auto result = solution.checkInclusion("ab",
        "eidbaooo");
    QuickSort(vec, 0, vec.size()-1);

    bfs();
    dijkstra();

    const int* ptr = new int(5);
    ptr = nullptr;

    return 0;
}

