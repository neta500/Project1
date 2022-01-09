#pragma once
#include <vector>

// [1,8,6,2,5,4,8,3,7] -> 49 (7x7)
// 그래프를 그렸을 때 최대로 물을 채울 수 있는 공간의 크기. 이건 사진보면 바로 이해됨.
// 결국 두 기둥을 기준으로 물을 채우게 되기 때문에, 기둥 index pair를 어떻게 고르느냐가 중요.
// array에서 pair를 뽑아내는 문제들은 hash_map, two pointers, slide window선에서 해결 가능하다.

// 1. brute force : 모든 index pair를 비교 O(n^2)
// 2. two pointers : 양쪽에서 좁혀오면서 비교하는건데 결국 std::min을 통해 height이
// 낮은 쪽으로 계산이 되기 때문에, 낮은 쪽만 pointer를 이동해주면 된다. O(n)

class Solution {
public:
    int maxArea(std::vector<int>& height) {
        int maxArea = 0;
        int left = 0;
        int right = height.size() - 1;

        while (left<right)
        {
            int width = right - left;
            maxArea = std::max(maxArea, width * std::min(height[right], height[left]));

            if (height[left] > height[right])
            {
                right--;
            }
            else
            {
                left++;
            }
        }

        return maxArea;
    }

    int maxArea_bruteforce(std::vector<int>& height) {
        int maxArea = 0;

        for (int i = 0; i < height.size(); ++i)
        {
	        for (int j = i + 1; j < height.size(); ++j)
	        {
                int width = j - i;
                int _height = std::min(height[i], height[j]);

                maxArea = std::max(maxArea, width * _height);
	        }
        }

        return maxArea;
    }
};