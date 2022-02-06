#pragma once
#include <vector>
#include <unordered_map>

// 0, 1의 개수가 같은 subarray의 maxLength 구하기
// [1,0,1,1,1] -> 0,1 쌍의 최대 개수는 1이므로, [0,1].size() = 2
// [1,0,1,0,1] -> 0,1 쌍의 최대 개수는 2이므로, [0,1,0,1].size() = 4

class Solution {
public:
    // hash_map, 현재 index까지의 0, 1들의 합을 저장해놓는다.
    int findMaxLength(std::vector<int>& nums) {
        std::unordered_map<int, int> map; // <sum, index>
        map.emplace(0, -1); // 처음은 합이 0, index -1로 시작

        int maxLen = 0; int sum = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            sum += nums[i] == 1 ? 1 : -1; // 1이면 +1, 0이면 -1해줌
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

    // brute force O(n^2) 0, 1 개수가 같은 모든 subarray를 구한다.
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