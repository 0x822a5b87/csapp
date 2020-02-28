#include "iostream"

int n, sum;

int a[101], m[101];

void init()
{
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int ai, mi;
		std::cin >> ai >> mi;
		a[i] = ai;
		m[i] = mi;

		std::cout << ai << " " << mi << std::endl;
	}
	std::cin >> sum;

	std::cout << "n = " << n << std::endl;
	std::cout << "sum = " << sum << std::endl;
}

/**
 * 假设从前面 n 个元素中取元素累加，如果可以达到 k，那么就设置 dp[n][k] = true
 */
bool solve1()
{
	bool dp[n + 1][sum + 1];
	for (int i = 0; i < n + 1; ++i)
		dp[i][0] = true;
	for (int j = 1; j < sum + 1; ++j)
		dp[0][j] = false;

	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < sum + 1; ++j)
		{
			dp[i][j] = false;
			// BUG：没有比较 j >= k * a[i - 1] 导致访问越界
			for (int k = 0; k <= m[i - 1] && j >= k * a[i - 1]; ++k)
			{
				dp[i][j] |= dp[i - 1][j - k * a[i - 1]];
			}
		}
	}

	std::cout << "================" << std::endl;
	for (int i = 0; i < n + 1; ++i)
	{
		for (int j = 0; j < sum + 1; ++j)
		{
			std::cout << dp[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "================" << std::endl;

	return dp[n][sum];
}

bool solve3()
{
	bool dp[n + 1][sum + 1];
	for (int i = 0; i < n + 1; ++i)
		dp[i][0] = true;
	for (int j = 1; j < sum + 1; ++j)
		dp[0][j] = false;

	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < sum + 1; ++j)
		{
			if (j >= a[i - 1])
			{
				dp[i][j] = dp[i - 1][j] | dp[i][j - a[i - 1]];
			}
			else
			{
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	std::cout << "================" << std::endl;
	for (int i = 0; i < n + 1; ++i)
	{
		for (int j = 0; j < sum + 1; ++j)
		{
			std::cout << dp[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "================" << std::endl;

	return dp[n][sum];
}

/*
 * dp[i][j] 表示从前面 i 个元素中累加得到 j 之后，剩余的 a[i-1] 数量，-1 表示不能累加得到 j
 */
bool solve2()
{
	int dp[n + 1][sum + 1];
	for (int j = 0; j < sum + 1; ++j)
		dp[0][j] = -1;
	for (int i = 1; i < n + 1; ++i)
		dp[i][0] = m[i - 1];

	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < sum + 1; ++j)
		{
			// BUG：这里我开始只判断了 > 0 没有判断 == 0
			if (dp[i - 1][j] >= 0)
			{
				// 前面 i - 1 个数字已经可以求和了，所以这里我们不用累加 a[i - 1]
				dp[i][j] = m[i - 1];
			}
			else if (j < a[i - 1] || dp[i][j - a[i - 1]] <= 0)
			{
				// i 个数字没办法通过求和得到 K - a[i - 1]，自然也没办法通过求和得到 K
				dp[i][j] = -1;
			}
			else
			{
				dp[i][j] = dp[i][j - a[i - 1]] - 1;
			}
		}
	}

	return dp[n][sum] > 0;
}

int main(int argc, char **argv)
{
	init();
	std::cout << solve1() << std::endl;
	std::cout << solve3() << std::endl;
}