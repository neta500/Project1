#pragma once
#include <vector>

// nums1�� �����°ǵ� �ε����� �� ����ȴ�.
// nums1�� ���� �ǵڿ� �ϳ�, num2�� ���� �ǵڿ� �ϳ�, �ű���� �ϳ� �̷��� 3���� �ε��� ���.

class Solution {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        int index1 = m - 1, index2 = n - 1, index_right = nums1.size() - 1;

        if (index2 < 0)
        {
            return;
        }

        while (index1 >= 0 && index2 >= 0)
        {
            const int num1 = nums1[index1];
            const int num2 = nums2[index2];

            if (num2 <= num1)
            {
                nums1[index_right] = num1;
                index_right--;
                index1--;
            }
            else
            {
                nums1[index_right] = num2;
                index_right--;
                index2--;
            }
        }

        while (index2 >= 0)
        {
            nums1[index_right] = nums2[index2];
            index_right--;
            index2--;
        }
    }
};