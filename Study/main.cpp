#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/Sorting.h"
#include "Algorithm/Graph.h"
#include "Algorithm/LeetCode/78_SubSet.h"
#include <deque>

using namespace sort;
using namespace graph;

int main()
{
    Solution solution;
    std::vector<int> vec{ 1,2,3 };
    std::vector<std::string> strVec{ "flow", "fly", "fleet" };
    const auto result = solution.subsets(vec);
    QuickSort(vec, 0, vec.size()-1);

    bfs();
    dijkstra();

    const int* ptr = new int(5);
    ptr = nullptr;


    std::vector<Cat> catVec;
    {
        Cat* cat = new Cat{};
        catVec.push_back(*cat);
        delete cat;
    }

    return 0;
}

