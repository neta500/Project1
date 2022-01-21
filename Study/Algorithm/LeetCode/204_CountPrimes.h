#pragma once
#include <vector>

// 소수 세기
// n = 10 -> 4개 (2,3,5,7)
// 기본적으로 n의 제곱근까지 수들로 자신을 나눠보면서 소수를 판별하는데, 이러면 시간이 안돼서
// 주어진 수 까지의 모든 소수를 구하기 위해서는 에라스토테네스의 체로 거른다.

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
            // 해당 숫자가 소수이면 (소수가 아니면 이미 이전의 소수의 배수에서 걸러짐)
	        if (isPrime[i] == true)
	        {
                // 해당 숫자의 배수들을 다 거른다.
                for (int j = i * i; j < n; j += i)
		        {
                    isPrime[j] = false;
		        }
	        }
        }


        return std::count(isPrime.begin(), isPrime.end(), true);
    }
};