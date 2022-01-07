#pragma once
#include <vector>

// nums1에 덮어씌우는건데 인덱스를 잘 쓰면된다.
// nums1의 숫자 맨뒤에 하나, num2의 숫자 맨뒤에 하나, 옮길곳에 하나 이렇게 3개의 인덱스 사용.

class Solution {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        int index1 = m - 1, index2 = n - 1, index_rightof_num1 = nums1.size() - 1;

        if (index2 < 0)
        {
            return;
        }

        while (index1 >= 0 && index2 >= 0)
        {
            const int num1 = nums1[index1];
            const int num2 = nums2[index2];

            // num1과 num2의 가장 큰 원소부터 비교해서, num1의 뒷부분(index_right)부터 채운다.
            if (num2 <= num1)
            {
                nums1[index_rightof_num1] = num1;
                index_rightof_num1--;
                index1--;
            }
            else
            {
                nums1[index_rightof_num1] = num2;
                index_rightof_num1--;
                index2--;
            }
        }

        while (index2 >= 0)
        {
            nums1[index_rightof_num1] = nums2[index2];
            index_rightof_num1--;
            index2--;
        }
    }
};