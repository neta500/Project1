#pragma warning(disable:4819)
#include <iostream>
#include "TestClass/TestClass.h"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include "Algorithm/LeetCode/763_PartitionLabels.h"

template <class T, class... Args>
void DoAsync()
{
    spdlog::info("{}")
}

void function(int a)
{
    spdlog::info("{}", a);
}

void function(int a, int b)
{
    spdlog::info("{}, {}", a, b);
}


int main()
{
    return 0;
}
