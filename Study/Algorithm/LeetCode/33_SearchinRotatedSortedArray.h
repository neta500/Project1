#pragma once
#include <vector>

// sorted array���� target�� ã�µ� O(logn)���� ã�¹� -> binary search 
// mid pivot�� ���ϰ�, target�� pivot���� ���ʿ� �ִ��� �����ʿ��ִ��� �ݺ�
// �̹����� sorted array�� � ����ŭ rotate�Ǿ��ִ�.
// ���� [0,1,2,4,5,6,7] �̾���ϴµ� �̰� [4,5,6,7,0,1,2]�� �Ǿ�����.
// [4,5,6,7,0,1,2]���� target 0 -> output 4

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int leftIndex = 0;
        int rightIndex = nums.size() - 1;

        while (leftIndex <= rightIndex)
        {
            int midIndex = (leftIndex + rightIndex) / 2;
            if (nums[midIndex] == target)
            {
                return midIndex;
            }

            // rotate�� ���
            if (nums[midIndex] > nums[rightIndex])
            {
	            if (nums[leftIndex] <= target && target < nums[midIndex])
	            {
                    rightIndex = midIndex - 1;
	            }
                else
                {
                    leftIndex = midIndex + 1;
                }
            }
            // rotate�� ���
            else if (nums[midIndex] < nums[leftIndex])
            {
	            if (nums[midIndex] < target && target <= nums[rightIndex])
	            {
                    leftIndex = midIndex + 1;
	            }
                else
                {
                    rightIndex = midIndex - 1;
                }
            }
            // rotate �ȵȰ��
            else
            {
	            if (target < nums[midIndex])
	            {
                    rightIndex = midIndex - 1;
	            }
                else
                {
                    leftIndex = midIndex + 1;
                }
            }
        }

        return -1;
    }
};