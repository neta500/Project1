#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/Sorting.h"
#include "Algorithm/Graph.h"
#include "Algorithm/LeetCode/1288_RemoveCoveredIntervals.h"
#include <deque>
#include <map>

using namespace sort;
using namespace graph;

class Test
{
public:
    int Get() const
    {
        std::scoped_lock lock(mMutex);
        spdlog::info("Get, mInt: {}", mInt);
        return mInt;
    }

    void Plus()
    {
        std::scoped_lock lock(mMutex);
        mInt++;
        spdlog::info("Plus, mInt: {}", mInt);
    }

    void Set(const int expected)
    {
        std::scoped_lock lock(mMutex);
        mInt = expected + 1;
        spdlog::info("Set, mInt: {}", mInt);
    }

    mutable std::mutex mMutex;
    int mInt = 0;
};

int main()
{
    Solution solution;
    /*std::vector<int> vec{ 1,2,3 };
    std::vector<std::string> strVec{ "flow", "fly", "fleet" };
    const auto result = solution.subsets(vec);
    QuickSort(vec, 0, vec.size()-1);

    bfs();
    dijkstra();

    const int* ptr = new int(5);
    ptr = nullptr;


    Animal* animal = new Cat();
    Cat* downCasted = dynamic_cast<Cat*>(animal);*/
    
    /*std::vector<std::vector<int>> vec
    {
        {1,4},
        {3,6},
        {2,8}
    };

    std::mutex mutex;

    Animal* cat = new Cat();
    Animal* dog = new Dog();

    const auto result = solution.removeCoveredIntervals(vec);

    boost::asio::io_context ioContext;

*/

    std::map<int, int> map;
    map.emplace(1, 1);
    map.emplace(2, 1);
    map.emplace(3, 1);
    map.emplace(4, 1);
    map.emplace(5, 1);

    auto found = map.find(1);
    if (found != map.end())
    {
        found->second++;
    }

    for (auto& [key, value] : map)
    {
        value++;
    }

    const auto& found2 = map.find(2);
    if (found2 != map.end())
    {
        found2->second++;
    }

    return 0;
}

