#include "iostream"

int n, m, mod;

void init()
{
	std::cin >> m;
	std::cin >> n;
	std::cin >> mod;
	std::cout << "n = " << n << std::endl;
	std::cout << "m = " << m << std::endl;
	std::cout << "mod = " << mod << std::endl;
}

int solve0(int i, int j)
{
	if (i == 1 || j == 0)
	{
		// 只剩一个盘子了，或者没有苹果了
		return 1;
	}
	else if (i > j)
	{
		// 盘子比苹果多
		return solve0(j, j);
	}
	else
	{
		// 1. 在每个盘子中都放一个苹果，然后将剩下的苹果放到盘子中
		// 2. 空出一个盘子不放苹果，将所有的苹果放到其他的盘子中
		// 空出两个或两个以上的盘子会在 2 中被递归出来
		return solve0(i, j - i) + solve0(i - 1, j);
	}
}

/*
 * dp[n][m] 表示 m 的 n 划分
 *
 * m == 盘子数量
 * n == 苹果数量
 */
int solve2()
{
	int dp[n + 1][m + 1];
	// 苹果为0
	for (int i = 0; i < n + 1; ++i)
		dp[i][0] = 1;
	// 盘子为1
	for (int j = 0; j < m + 1; ++j)
		dp[1][j] = 1;

	for (int i = 2; i < n + 1; ++i)
	{
		for (int j = 1; j < m + 1; ++j)
		{
			if (j >= i)
				dp[i][j] = dp[i][j - i] + dp[i - 1][j];
			else
				dp[i][j] = dp[j][j];
		}
	}

	return dp[n][m];
}

int main(int argc, char **argv)
{
	init();
	std::cout << solve0(n, m) << std::endl;
	std::cout << solve2() << std::endl;
}