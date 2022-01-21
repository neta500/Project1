#pragma once
#include <vector>

// �Ҽ� ����
// n = 10 -> 4�� (2,3,5,7)
// �⺻������ n�� �����ٱ��� ����� �ڽ��� �������鼭 �Ҽ��� �Ǻ��ϴµ�, �̷��� �ð��� �ȵż�
// �־��� �� ������ ��� �Ҽ��� ���ϱ� ���ؼ��� �������׳׽��� ü�� �Ÿ���.

class Solution {
public:
    bool IsPrime(const int num)
    {
        if (num < 2)
        {
            return false;
        }

	    for (int i = 2; i <= std::sqrt(num); ++i)
	    {
		    if (num % i == 0)
		    {
                return false;
		    }
	    }

        return true;
    }

    int countPrimes(int n) {
        std::vector<bool> isPrime(n, true);
        isPrime[0] = false; isPrime[1] = false;

        for (int i = 0; i < std::sqrt(n); ++i)
        {
            // �ش� ���ڰ� �Ҽ��̸� (�Ҽ��� �ƴϸ� �̹� ������ �Ҽ��� ������� �ɷ���)
	        if (isPrime[i] == true)
	        {
                // �ش� ������ ������� �� �Ÿ���.
                for (int j = i * i; j < n; j += i)
		        {
                    isPrime[j] = false;
		        }
	        }
        }


        return std::count(isPrime.begin(), isPrime.end(), true);
    }
};