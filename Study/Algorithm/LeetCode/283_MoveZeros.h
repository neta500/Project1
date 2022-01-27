#pragma once
#include <vector>

// STL Container의 erase-remove idiom을 생각하면 효율적으로 문제를 해결할 수 있다.
// 그냥 컨테이너를 처음부터 끝까지 순회하면서 0을 찾아서 삭제하고, 뒤에 붙이면 되지만..

class Solution
{
public:
	void moveZeroes(std::vector<int>& nums)
	{
		int lastNonZeroIndex = 0;
		for (int curr = 0; curr < nums.size(); ++curr)
		{
			// 0이 아닌 원소를 찾아서, 앞에서부터 차곡차곡 채워넣는다.
			if (nums[curr] != 0)
			{				
				nums[lastNonZeroIndex] = nums[curr];
				lastNonZeroIndex++;
			}
		}

		// 뒷부분 0으로 밀어준다.
		for (int i = lastNonZeroIndex; i < nums.size(); ++i)
		{
			nums[i] = 0;
		}
	}
};