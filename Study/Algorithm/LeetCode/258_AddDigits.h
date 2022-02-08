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
                // 1�� �ڸ����� 10���� ������ ���Ѵ�.
                sum += num % 10; // 38�� 10���� ������ 3 (������ 8) �̹Ƿ� sum�� 8�߰�
                num /= 10; // num�� 10���� ���� �� �����. (38->3)
	        }

            num = sum;
            sum = 0;
        }

        return num;
    }
};