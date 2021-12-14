#pragma once
#include <vector>

// 1. brute force : 모든 순서쌍을 구해서 비교한 후 같은거 찾아냄 O(n^2)
// 2. sorting : 정렬 후 한바퀴 돌면서 순서쌍이 같은걸 찾아냄 정렬하는데 드는 비용 O(nlogn)
// 3. 별도의 array를 만들고, flag를 올려가며 카운팅. O(n) + space O(n)
// 4. 별도의 array를 만들지 않고, 주어진 array에서 flag를 카운팅한다. O(n) + space O(1)
// 5. swap
// 6. Floyd's Tortoise and Hare

class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[std::abs(nums[i])] < 0)
            {
                return std::abs(nums[i]);
            }
            else
            {
                nums[std::abs(nums[i])] *= -1;
            }
        }

        return 0;
    }
};