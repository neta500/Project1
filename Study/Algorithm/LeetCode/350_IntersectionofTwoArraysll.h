#pragma once
#include <vector>
#include <unordered_map>

// [1,2,2,1] [2,2] -> [2,2]
// [4,9,5] [9,4,9,8,4] -> [4,9] or [9,4]
// array���� ���ڼ���� hash_map +-�� �ذ��� �� �������� ����.

class Solution {
public:
    std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_map<int, int> map;
        for (const int num : nums1)
        {
            // ù��° �迭�� �־��ְ�
            map[num]++;
        }

        std::vector<int> result;
        for (const int num : nums2)
        {            
            // �ι�° �迭�� ���ְ�
            if (map.find(num) != map.end())
            {
                map[num]--;
                // �������� 0�̻��̴�? ��ģ�ٴ� ���̹Ƿ� ����� �߰�
                // ���µ� 0���� ������ �迭2�� �ش� ���� ������ �� ���ٴ� ���̴� �н�
                if (map[num] >= 0)
                {
                    result.push_back(num);
                }
            }
        }

        return result;
    }
};