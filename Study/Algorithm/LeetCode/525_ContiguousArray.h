#pragma once
#include <vector>
#include <unordered_map>

// 0, 1�� ������ ���� subarray�� maxLength ���ϱ�
// [1,0,1,1,1] -> 0,1 ���� �ִ� ������ 1�̹Ƿ�, [0,1].size() = 2
// [1,0,1,0,1] -> 0,1 ���� �ִ� ������ 2�̹Ƿ�, [0,1,0,1].size() = 4

class Solution {
public:
    // hash_map, ���� index������ 0, 1���� ���� �����س��´�.
    int findMaxLength(std::vector<int>& nums) {
        std::unordered_map<int, int> map; // <sum, index>
        map.emplace(0, -1); // ó���� ���� 0, index -1�� ����

        int maxLen = 0; int sum = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            sum += nums[i] == 1 ? 1 : -1; // 1�̸� +1, 0�̸� -1����
            if (map.find(sum) != map.end())
            {
                maxLen = std::max(maxLen, i - map[sum]);
            }
            else
            {
                map.emplace(sum, i);
            }
        }

        return maxLen;
    }

    // brute force O(n^2) 0, 1 ������ ���� ��� subarray�� ���Ѵ�.
    int findMaxLength_bruteforce(std::vector<int>& nums) {
        int maxLen = 0;
        for (int start = 0; start < nums.size(); ++start)
        {
            int zeroes = 0; int ones = 0;
            for (int end = start; end < nums.size(); ++end)
            {
	            if (nums[end] == 0)
	            {
                    zeroes++;
	            }
                else
                {
                    ones++;
                }

                if (zeroes == ones)
                {
                    maxLen = std::max(maxLen, end - start + 1);
                }
            }            
        }

        return maxLen;
    }
};