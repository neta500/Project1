#pragma once
#include <vector>
#include <numeric>
#include <set>

// 1. 그냥 sort를 한다. quick sort 기준 O(nlogn)
// 2. 어차피 0, 1, 2만 있으니까 각각 숫자를 세서 새 배열에 차례로 집어넣는다. O(n)
// 3. in-place swap(배열 내 스왑): 3 pointer O(n)

class Solution {
public:
    // in-place swap (배열 내 스왑)
    void sortColors(std::vector<int>& nums) {
        int index0 = 0; // 0을 찾으면 스왑
        int index_left = 0; // 좌측 스왑용
        int index_right = static_cast<int>(nums.size() - 1); // 우측 스왑용

        while (index0 <= index_right)
        {
            if (nums[index0] == 0)
            {
                std::swap(nums[index0], nums[index_left]);

                index0++;
                index_left++;
            }
            else if (nums[index0] == 2)
            {
                std::swap(nums[index0], nums[index_right]);

                index_right--;
            }
            else if (nums[index0] == 1)
            {
                index0++;
            }
        }
    }

    // 그냥 quick sort
    // 1. pivot하나를 잡고, 왼쪽에는 작은숫자를, 오른쪽에는 큰숫자를 배치한다. 이걸 반복한다.
    void sortColors_2(std::vector<int>& nums) {
        quickSort(nums, 0, static_cast<int>(nums.size()) - 1);
    }

    void quickSort(std::vector<int>& nums, int left, int right)
    {
        if (left < right)
        {
            const int partitionIndex = partition(nums, left, right);
            quickSort(nums, left, partitionIndex - 1);
            quickSort(nums, partitionIndex + 1, right);
        }
    }

    int partition(std::vector<int>& nums, int left, int right) {
        const int pivot = nums[right];

        int index = left - 1;

        for (int i = left; i < right; ++i)
        {
            if (nums[i] <= pivot)
            {
                index++;
                std::swap(nums[index], nums[i]);
            }
        }

        std::swap(nums[index + 1], nums[right]);

        return index+1;
    }
};