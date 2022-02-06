#pragma once
#include <vector>
#include <spdlog/spdlog.h>

// �迭���� �ߺ��� �����ؾ��ϴµ�, �ߺ� ���Ҵ� 2������ ������ �� ����.
// �ߺ��� ���ŵ� �迭�� ũ���, �迭�� return
// ���ŵ� �ڸ��� _�� ǥ��
// [1,1,1,2,2,3] -> 5, [1,1,2,2,3,_]
// �⺻������, ����Ī(shifting)�� �ϴ°� �´µ�..
// ������ �ΰ� �����ϸ鼭, �ڿ��ִ°� �տ��ִ°Ŷ� �ٲ��ش�.

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