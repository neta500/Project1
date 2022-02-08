#pragma once

// 38 --> 3 + 8 --> 11
// 11 --> 1 + 1 --> 2
// 0 --> 0

class Solution {
public:
    int addDigits(int num) {
        int sum = 0;

        while (num > 9)
        {
	        while (num != 0)
	        {
                // 1의 자리부터 10으로 나눠서 구한다.
                sum += num % 10; // 38을 10으로 나누면 3 (나머지 8) 이므로 sum에 8추가
                num /= 10; // num은 10으로 나눈 몫만 남긴다. (38->3)
	        }

            num = sum;
            sum = 0;
        }

        return num;
    }
};