#pragma once
#include <vector>
#include <unordered_set>
#include <numeric>
#include <functional>

// [4,1,2,1,2] -> 4
// �Ѱ��� �����ϴ� ����ã���ε�
// 1. hash�� �̿��Ѵ�. -> T O(N) + S O(N) 
// 2. bitset�� �̿��Ѵ�. -> T O(N) + S ����

class Solution {
public:
    int singleNumber_hash(std::vector<int>& nums) {
        std::unordered_set<int> set;

        // set�� �־��� ���� �������, ������ ���� ���Ҹ� return ���ش�.
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
        // ���� ���ڸ� xor�ϸ� 0�� �Ǵ°��� �̿��ؼ� �ϴ� xor �����ش�.
        return std::accumulate(nums.begin(), nums.end(), 0, std::bit_xor<int>{});
    }
};