#pragma once
#include <vector>
#include <unordered_map>

// 4�� ���� ������ ���� 0�̵Ǵ� ����� �� ã��

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
                // ���� 1, 1, -1, -1�̸� a,b���� map[2] = 1,
                // c,d���� -1, -1�� map[2]�� �˻��ϰ� �Ǵ� ����� ���� �ȴ�.
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

        // time complexity : ��� vec�� ũ�Ⱑ n�̹Ƿ� O(n^2)
        return result;
    }
};