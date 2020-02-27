// 完全背包问题
#include "iostream"

int n, weight;
int w[100], v[100];

void init()
{
	int w0, v0;
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> w0 >> v0;
		w[i] = w0;
		v[i] = v0;
		std::cout << w[i] << " " << v[i] << std::endl;
	}
	std::cin >> weight;

	std::cout << "n = " << n << std::endl;
	std::cout << "w = " << weight << std::endl;
}

/**
 * 从 [0, x - 1] 项元素里面，选择重量不超过 y 的物品。价值越高越好
 */
int solve(int x, int y)
{
	// 初始化 dp 数组
	int dp[x + 1][y + 1];
	for (size_t i = 0; i != x + 1; ++i)
		dp[i][0] = 0;
	for (size_t j = 0; j != y + 1; ++j)
		dp[0][j] = 0;

	for (size_t i = 1; i <= x; ++i)
	{
		for (size_t j = 1; j <= y; ++j)
		{
			int max = 0;
			for (size_t k = 0; k * w[i-1] <= j; ++k)
			{
				int tmp = dp[i - 1][j - k * w[i-1]] + static_cast<int>(k) * v[i-1];
				if (max < tmp)
				{
					max = tmp;
				}
			}
			dp[i][j] = max;
		}
	}

	return dp[x][y];
}


int solve2(int x, int y)
{
	// 初始化 dp 数组
	int dp[x + 1][y + 1];
	for (size_t i = 0; i != x + 1; ++i)
		dp[i][0] = 0;
	for (size_t j = 0; j != y + 1; ++j)
		dp[0][j] = 0;

	for (size_t i = 1; i <= x; ++i)
	{
		for (size_t j = 1; j <= y; ++j)
		{
			// 这里我犯了两个错误
			// 1. 第一次我没有判断 j >= w[j - 1] 就开始计算实际的值，导致数据会访问到 0 以后的索引
			// 2. 第二次判断了 j >= w[j - 1]，但是在不符合条件的时候没有赋值
			// dp[i][j] = dp[i - 1][j];
			// 这导致了部分数据未赋值
			if (j >= w[i - 1])
			{
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - w[i - 1]] + v[i - 1]);
			}
			else
			{
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	std::cout << "====================" << std::endl;
	for (size_t i = 0; i <= n; ++i)
	{
		for (size_t j = 0; j <= weight; ++j)
		{
			std::cout << dp[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "====================" << std::endl;

	return dp[x][y];
}


/*
 * 注意，这个是完全背包问题的错误解法，我实现的时候包含了两个错误
 */
int solve3(int x, int y)
{
	// 初始化 dp 数组
	int dp[y + 1];
	for (size_t j = 0; j != y + 1; ++j)
		dp[j] = 0;

	for (size_t i = 1; i <= x; ++i)
	{
		// 错误1：这里我最开始使用的是 ++j
		for (size_t j = w[i-1]; j <= weight; ++j)
		{
			if (j >= w[i - 1])
			{
				/*
				 * 错误2：
				 * 注意到完全背包问题和不完全背包问题的状态变换公式是不一样的。
				 * 完全背包问题的状态变换公式是：
				 * dp[i+1][j] = std::max(dp[i][j],
				 * 						 dp[i + 1][j - w[i]] + v[i])
				 *
				 * 注意，这里有个问题是：std::max() 的第二个参数是 dp[i+1] 而不是 dp[i]。
				 * 按照我们之前的说法，这个以为数组小于 j 的部分，代表的其实是 dp[i] 的那一行。
				 * 所以，我们这个解法退化成了不完全背包问题。
				 */
				dp[j] = std::max(dp[j],
								 dp[j - w[i - 1]] + v[i - 1]);
			}
			else
			{
				dp[j] = dp[j];
			}
		}
	}

	std::cout << "====================" << std::endl;
	for (size_t j = 0; j <= weight; ++j)
	{
		std::cout << dp[j] << " ";
	}
	std::cout << std::endl;
	std::cout << "====================" << std::endl;

	return dp[y];
}

int main(int argc, char **argv)
{
	init();
	std::cout << solve(n, weight) << std::endl;
	std::cout << solve2(n, weight) << std::endl;
	std::cout << solve3(n, weight) << std::endl;
}
