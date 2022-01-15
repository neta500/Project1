#pragma once
#include <vector>

// #greedy
// �� index���� ���Ұ���ŭ ������ �����ϴ�.
// [2,3,1,1,4] -> index 0���� 2ĭ���� ��������, 1����-> index 1���� 3�����ؼ� last���� ����


class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        int farest = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
	        if (farest < i)
	        {
                return false;
	        }

            farest = std::max(i + nums[i], farest);
        }

        return true;
    }
};