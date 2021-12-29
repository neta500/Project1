#pragma once
#include <vector>
#include <unordered_map>

// [1,2,2,1] [2,2] -> [2,2]
// [4,9,5] [9,4,9,8,4] -> [4,9] or [9,4]
// array문제 숫자세기는 hash_map +-로 해결할 수 있을때가 많음.

class Solution {
public:
    std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_map<int, int> map;
        for (const int num : nums1)
        {
            // 첫번째 배열은 넣어주고
            map[num]++;
        }

        std::vector<int> result;
        for (const int num : nums2)
        {            
            // 두번째 배열은 빼주고
            if (map.find(num) != map.end())
            {
                map[num]--;
                // 빼고나서도 0이상이다? 겹친다는 뜻이므로 결과에 추가
                // 뺐는데 0보다 작으면 배열2에 해당 원소 개수가 더 많다는 뜻이니 패스
                if (map[num] >= 0)
                {
                    result.push_back(num);
                }
            }
        }

        return result;
    }
};