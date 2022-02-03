#pragma once
#include <vector>
#include <unordered_map>

// 4개 벡터 원소의 합이 0이되는 경우의 수 찾기

class Solution {
public:
    int fourSumCount(
        std::vector<int>& nums1,
        std::vector<int>& nums2,
        std::vector<int>& nums3,
        std::vector<int>& nums4)
	{
        int result = 0;
        std::unordered_map<int, int> map;

    	for (const int a : nums1)
        {
	        for (const int b : nums2)
	        {
                // 만약 1, 1, -1, -1이면 a,b에서 map[2] = 1,
                // c,d에서 -1, -1로 map[2]를 검색하게 되니 경우의 수가 된다.
                map[a + b]++;
	        }
        }

        for (const int c : nums3)
        {
	        for (const int d : nums4)
	        {
                result += map[-c - d];
	        }
        }

        // time complexity : 모든 vec의 크기가 n이므로 O(n^2)
        return result;
    }
};