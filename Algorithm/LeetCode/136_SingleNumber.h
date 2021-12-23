#pragma once
#include <vector>
#include <unordered_set>
#include <numeric>
#include <functional>

// [4,1,2,1,2] -> 4
// 한개만 존재하는 숫자찾기인데
// 1. hash를 이용한다. -> T O(N) + S O(N) 
// 2. bitset을 이용한다. -> T O(N) + S 없음

class Solution {
public:
    int singleNumber_hash(std::vector<int>& nums) {
        std::unordered_set<int> set;

        // set에 넣었다 빼는 방식으로, 마지막 남은 원소를 return 해준다.
        for (const int num : nums)
        {
            if (set.contains(num))
            {
                set.erase(num);
            }
            else
            {
                set.emplace(num);
            }
        }

        return *set.begin();
    }

    int singleNumber(std::vector<int>& nums) {
        // 같은 숫자를 xor하면 0이 되는것을 이용해서 싹다 xor 갈겨준다.
        return std::accumulate(nums.begin(), nums.end(), 0, std::bit_xor<int>{});
    }
};