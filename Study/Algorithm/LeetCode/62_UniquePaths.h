#pragma once
#include <vector>

// ���� m, ���� n�� grid�� �־�������, grid ������ ���ۺ��� �����ʾƷ� ������ �� �� �ִ� ����� ��
// m = 3, n = 2�� ��� right down down, down right down, down down right 3����
// ��ã���ε� DP �����̴�.
// ���������� �� �� �ִ� ����� ���� �� ������ �� �� �ִ� ����� ������ ���� �� �ֱ� ����.
// �̰� ���ɹ�����. ��ã�� + ����

class Solution {
public:
    // 1. brute force O(2^(m+n))
    // ��� ����� ���� ���Ѵ�. with recurrsion
    int uniquePaths_bruteforce(int m, int n, int i = 0, int j = 0) {
        // ���� ������ ����
        if (i >= m || j >= n) return 0;

        // ������ ������ ������ ���
        if (i == m - 1 && j == n - 1) return 1;

        // i�� j�� ���� 1 ����(���������� ��ĭ, �Ʒ��� ��ĭ ���鼭)��Ű�鼭 �ݺ�
        return uniquePaths_bruteforce(m, n, i + 1, j) + uniquePaths_bruteforce(m, n, i, j + 1);
    }

    // 2. DP - Memoization O(mn)
    // brute force����� �ߺ������ ��û���� ������, �̹� ���� ��Ʈ�� �����̳ʿ� �����Ѵ�.
    int dp_arr[101][101]{};
    int uniquePaths_dp_memo(int m, int n, int i = 0, int j = 0)
    {
    	if (i >= m || j >= n) return 0;
        if (i == m - 1 && j == n - 1) return 1;

        if (dp_arr[i][j] == 0) return dp_arr[i][j];
        return dp_arr[i][j] = uniquePaths_dp_memo(m, n, i + 1, j) + uniquePaths_dp_memo(m, n, i, j + 1);
    }

    // 3. DP - Tabulation
    // Memoization�� top down�̴�, bottom up ������� �ٲ㺸��.
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
    // ���� m-1, ���� n-1�� ��ã�� ���տ���, �Ϸķ� �����ϴ� ����� ���̹Ƿ�,
    // (m-1 + n-1)! / (m-1)! * (n-1)! �� ���� ����ȭ�ϸ�,
    // (m+n-2)*(m+n-3)*...(m) / (n-1)*...2*1 �̹Ƿ� �̸� for������ ��Ÿ���� �ȴ�.
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