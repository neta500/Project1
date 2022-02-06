#pragma once
#include <vector>
#include <spdlog/spdlog.h>

// 배열에서 중복을 제거해야하는데, 중복 원소는 2개까지 존재할 수 있음.
// 중복이 제거된 배열의 크기와, 배열을 return
// 제거된 자리는 _로 표기
// [1,1,1,2,2,3] -> 5, [1,1,2,2,3,_]
// 기본적으로, 스위칭(shifting)을 하는게 맞는데..
// 포인터 두개 유지하면서, 뒤에있는걸 앞에있는거랑 바꿔준다.

class Solution {
public:
    void Print(const std::vector<int>& nums)
    {
        std::string str;
        for (const int n : nums)
        {
            str.append(std::to_string(n) + " ");
        }

        spdlog::info(str);
    }

    int removeDuplicates(std::vector<int>& nums) {
        int i = 0;
        for (const int n : nums)
        {
            if (i < 2 || n > nums[i - 2])
	        {
                nums[i] = n;
                i++;
	        }
        }

        return i;
    }
};