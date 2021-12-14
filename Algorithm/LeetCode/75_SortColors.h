#pragma once
#include <vector>
#include <numeric>
#include <set>

// 1. �׳� sort�� �Ѵ�. quick sort ���� O(nlogn)
// 2. ������ 0, 1, 2�� �����ϱ� ���� ���ڸ� ���� �� �迭�� ���ʷ� ����ִ´�. O(n)
// 3. in-place swap(�迭 �� ����): 3 pointer O(n)

class Solution {
public:
    // in-place swap (�迭 �� ����)
    void sortColors(std::vector<int>& nums) {
        int index0 = 0; // 0�� ã���� ����
        int index_left = 0; // ���� ���ҿ�
        int index_right = static_cast<int>(nums.size() - 1); // ���� ���ҿ�

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

    // �׳� quick sort
    // 1. pivot�ϳ��� ���, ���ʿ��� �������ڸ�, �����ʿ��� ū���ڸ� ��ġ�Ѵ�. �̰� �ݺ��Ѵ�.
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