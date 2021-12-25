#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> hash_map;

        for (const int num : nums)
        {
            hash_map[num]++;
        }

        // heap에 넣는다.
        auto func = [&hash_map](const int n1, const int n2)
        {
            return hash_map[n1] > hash_map[n2];
        };
        std::priority_queue<int, std::vector<int>, decltype(func)> heap(func);

        for (const auto& [num, count] : hash_map)
        {
            heap.push(num);
            if (heap.size() > k)
            {
                heap.pop();
            }
        }

        std::vector<int> result;
        while(false == heap.empty())
        {
            if (result.size() < k)
            {
                result.emplace_back(heap.top());
                heap.pop();
            }
        }


        return result;
    }
};
