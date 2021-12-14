#pragma once
#include <vector>
#include <numeric>
#include <set>

class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums)
    {
        // sliding window O(n)
        int left = 0, right = 0, sum = 0, minlen = INT_MAX;
        for (auto i = 0; i < nums.size(); ++i)
        {
            sum += nums[right];            
            right++;
            while (sum >= target)
            {
                minlen = std::min(minlen, right - left);
                sum -= nums[left];
                left++;
            }
        }

        return minlen == INT_MAX ? 0 : minlen;
    }

    int minSubArrayLen_bruteForce(int target, std::vector<int>& nums) {
        // brute force O(n^2)
        int sum = 0;

        std::set<int> lengthSet;

        for (auto i = 0; i < nums.size()-1; ++i)
        {
            for (auto j = i; j < nums.size() - 1; ++j)
            {
                sum += nums[j];
                if (target == sum)
                {
                    if (i == j)
                    {
                        lengthSet.emplace(1);
                    }
                    else
                    {
                        lengthSet.emplace(j - i);
                    }
                }
            }

            sum = 0;
        }

        if (lengthSet.empty())
        {
            return 0;
        }
        else
        {
            return *lengthSet.begin();
        }
        
        return 0;
    }
};