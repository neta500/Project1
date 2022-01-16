#pragma once
#include <vector>

// 세로 m, 가로 n의 grid가 주어졌을때, grid 왼쪽위 시작부터 오른쪽아래 끝까지 갈 수 있는 경로의 수
// m = 3, n = 2인 경우 right down down, down right down, down down right 3가지
// 길찾기인데 DP 문제이다.
// 마지막까지 갈 수 있는 경우의 수는 그 전까지 갈 수 있는 경우의 수에서 구할 수 있기 때문.
// 이거 수능문제다. 길찾기 + 순열

class Solution {
public:
    // 1. brute force O(2^(m+n))
    // 모든 경우의 수를 구한다. with recurrsion
    int uniquePaths_bruteforce(int m, int n, int i = 0, int j = 0) {
        // 벽에 닿으면 리턴
        if (i >= m || j >= n) return 0;

        // 마지막 지점에 도착한 경우
        if (i == m - 1 && j == n - 1) return 1;

        // i와 j를 각각 1 증가(오른쪽으로 한칸, 아래로 한칸 가면서)시키면서 반복
        return uniquePaths_bruteforce(m, n, i + 1, j) + uniquePaths_bruteforce(m, n, i, j + 1);
    }

    // 2. DP - Memoization O(mn)
    // brute force방법은 중복계산이 엄청많기 때문에, 이미 계산된 루트는 컨테이너에 저장한다.
    int dp_arr[101][101]{};
    int uniquePaths_dp_memo(int m, int n, int i = 0, int j = 0)
    {
    	if (i >= m || j >= n) return 0;
        if (i == m - 1 && j == n - 1) return 1;

        if (dp_arr[i][j] == 0) return dp_arr[i][j];
        return dp_arr[i][j] = uniquePaths_dp_memo(m, n, i + 1, j) + uniquePaths_dp_memo(m, n, i, j + 1);
    }

    // 3. DP - Tabulation
    // Memoization은 top down이니, bottom up 방식으로 바꿔보자.
    int uniquePaths_dp_tab(int m, int n)
    {
        std::vector dp(m, std::vector(n, 1));
        for (int i = 1; i < m; ++i)
        {
	        for (int j = 1; j < n; ++j)
	        {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
	        }
        }

        return dp[m - 1][n - 1];
    }

    // 4. DP - Space optimized    
    int uniquePaths_dp_opt(int m, int n)
    {
        std::vector dp(n, 1);
        for (int i = 1; i < m; ++i)
        {
	        for (int j = 1; j < n; ++j)
	        {
                dp[j] += dp[j - 1];
	        }
        }

        return dp[n - 1];
    }

    // 5. Math Combination
    // 가로 m-1, 세로 n-1의 길찾기 조합에서, 일렬로 나열하는 경우의 수이므로,
    // (m-1 + n-1)! / (m-1)! * (n-1)! 이 식을 최적화하면,
    // (m+n-2)*(m+n-3)*...(m) / (n-1)*...2*1 이므로 이를 for문으로 나타내면 된다.
    int uniquePaths_math(int m, int n)
    {
        long ans = 1;
        for (int i = m + n - 2, j = 1; i >= std::max(m, n); --i, ++j)
        {
            ans = (ans * i) / j;
        }
        return ans;
    }
    
    int uniquePaths_gamma(int m, int n)
    {
        return static_cast<int>(tgamma(m + n - 1) / (tgamma(m) * tgamma(n)));
    }
};