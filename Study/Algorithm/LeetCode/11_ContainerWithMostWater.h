#pragma once
#include <vector>

// [1,8,6,2,5,4,8,3,7] -> 49 (7x7)
// �׷����� �׷��� �� �ִ�� ���� ä�� �� �ִ� ������ ũ��. �̰� �������� �ٷ� ���ص�.
// �ᱹ �� ����� �������� ���� ä��� �Ǳ� ������, ��� index pair�� ��� �����İ� �߿�.
// array���� pair�� �̾Ƴ��� �������� hash_map, two pointers, slide window������ �ذ� �����ϴ�.

// 1. brute force : ��� index pair�� �� O(n^2)
// 2. two pointers : ���ʿ��� �������鼭 ���ϴ°ǵ� �ᱹ std::min�� ���� height��
// ���� ������ ����� �Ǳ� ������, ���� �ʸ� pointer�� �̵����ָ� �ȴ�. O(n)

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