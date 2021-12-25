#pragma once
#include <vector>

// STL Container의 erase-remove idiom을 생각하면 효율적으로 문제를 해결할 수 있다.
// 그냥 컨테이너를 처음부터 끝까지 순회하면서 0을 찾아서 삭제하고, 뒤에 붙이면 되지만..

class Solution
{
public:
	void moveZeroes(std::vector<int>& nums)
	{
		int wIndex = 0;
			
		for (auto i = 0; i < nums.size(); ++i)
		{
			// wIndex가 가리키는 값이 0이 아니면 shift하는것을 반복.
			if (nums[i] != 0)
			{
				nums[wIndex] = nums[i];
				wIndex++;
			}
		}

		for (; wIndex < nums.size(); ++wIndex)
		{
			nums[wIndex] = 0;
		}
	}
};