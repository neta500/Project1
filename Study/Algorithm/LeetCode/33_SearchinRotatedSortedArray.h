#pragma once
#include <vector>

// sorted array에서 target을 찾는데 O(logn)으로 찾는법 -> binary search 
// mid pivot을 정하고, target이 pivot기준 왼쪽에 있는지 오른쪽에있는지 반복
// 이문제는 sorted array가 어떤 값만큼 rotate되어있다.
// 원래 [0,1,2,4,5,6,7] 이어야하는데 이게 [4,5,6,7,0,1,2]로 되어있음.
// [4,5,6,7,0,1,2]에서 target 0 -> output 4

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

            // rotate된 경우
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
            // rotate된 경우
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
            // rotate 안된경우
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