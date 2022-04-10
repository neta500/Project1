#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <mutex>
#include "Algorithm/Sorting.h"
#include "Algorithm/Graph.h"
#include "Algorithm/LeetCode/1029_TwoCityScheduling.h"
#include <deque>
#include <map>
#include <format>

using namespace sort;
using namespace graph;

//template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
template <class T> requires std::integral<T>
void TestInt(T t)
{
    std::cout << t << '\n';
}

int main()
{
    /*Solution solution;
    std::vector<std::vector<int>> costs{ {10,20}, {30,200}, {400,50}, {30,20} };
    const auto result = solution.twoCitySchedCost_greedy(costs);*/

    std::vector<std::byte> vec;
    vec.emplace_back(static_cast<std::byte>('1'));
    vec.emplace_back(static_cast<std::byte>('2'));
    vec.emplace_back(static_cast<std::byte>('3'));
    vec.emplace_back(static_cast<std::byte>('4'));
    vec.emplace_back(static_cast<std::byte>('5'));
    vec.emplace_back(static_cast<std::byte>('6'));
    vec.emplace_back(static_cast<std::byte>('7'));

    std::string str(reinterpret_cast<const char*>(&vec[0]), vec.size());

    return 0;
}


