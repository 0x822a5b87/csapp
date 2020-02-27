// 01 背包问题

#include "iostream"

int  n, W;
int  items[100][2];
int  dp[101][10001];
bool is_init = false;

void init()
{
	std::cin >> n;
	int w0, v0, tmp = 0;
	while (tmp++ < n)
	{
		std::cin >> w0 >> v0;
		items[tmp][0] = w0;
		items[tmp][1] = v0;
	}
	std::cin >> W;
}

void print_array()
{
	std::cout << "=================" << std::endl;
	for (size_t i = 0; i <= n; ++i)
	{
		for (size_t j = 0; j <= W; ++j)
		{
			std::cout << dp[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "=================" << std::endl;
}

int exhaustion(int i, int weight)
{
	if (i == n)
	{
		return 0;
	}
	else if (weight < items[i][0])
	{
		return exhaustion(++i, weight);
	}
	else
	{
		// 选择和不选择物品都尝试，并取得最大值
		return std::max(exhaustion(i + 1, weight),
						exhaustion(i + 1, weight - items[i][0]) + items[i][1]);
	}
}

int dp_res(int i, int weight)
{
	if (!is_init)
	{
		memset(dp, -1, sizeof(dp));
		is_init = true;
	}
	if (dp[i][weight] >= 0)
		return dp[i][weight];

	int res;
	if (i == n)
	{
		res = 0;
	}
	else if (weight < items[i][0])
	{
		res = dp_res(i + 1, weight);
	}
	else
	{
		res = std::max(dp_res(i + 1, weight),
					   dp_res(i + 1, weight - items[i][0]) + items[i][1]);
	}

	return res;
}

/**
 * 数组的元素 dp[x][y] 表示：
 *
 * 从第 x 个元素开始选择，当前负重为 y 的最大价值
 */
int dp_func(int index, int weight)
{
	for (int i = 0; i <= 10001; ++i)
	{
		dp[n][i] = 0;
	}

	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = 0; j <= W; j++)
		{
			// j 小于 items[i][0]，说明 dp[i][j] 无法选择 items[i] 元素
			// 所以它可以简单的等于它的上面一层
			if (j < items[i][0])
			{
				dp[i][j] = dp[i + 1][j];
			}
			else
			{
				// j 大于 items[i][0]，表示它可以选择 items[i] 元素，
				// 所以它需要做一个比较，选择两个值中的较大值
				// 1. 不选择 items[i]
				// 2. 选择 items[i]，当选择 items[i] 时，它的最大值等于 dp[i+1][j-items[i][0]] + items[i][1]
				dp[i][j] = std::max(dp[i + 1][j],
									dp[i + 1][j - items[i][0]] + items[i][1]);
			}
		}
	}

	return dp[index][weight];
}

/**
 * 表示从 [0, num] 的区间取，取出的最多不超过重量 weight 的物品
 */
int dp_func2(int num, int weight)
{
	for (size_t i = 0; i < W; ++i)
	{
		dp[0][i] = 0;
	}

	for (size_t i = 1; i <= n; ++i)
	{
		for (size_t j = 0; j <= W; ++j)
		{
			if (j < items[i - 1][0])
			{
				dp[i][j] = dp[i - 1][j];
			}
			else
			{
				dp[i][j] = std::max(dp[i - 1][j],
									dp[i - 1][j - items[i - 1][0]] + items[i - 1][1]);
			}
		}
	}

	print_array();
	return dp[num][weight];
}

/*
 * 对 dp 数组进行优化，只需要一维数组就可以。
 * dp[i][j] 代表从前面 i 个元素开始，选择不大于重量 weight 的物品
 */
int dp_func3(int num, int weight)
{
	// 这里我出了一个 BUG，我没有初始化数组中所有的值。
	int dp0[weight + 1];
	memset(dp0, 0, sizeof(dp0));

	for (size_t i = 1; i <= num; ++i)
	{
		for (size_t j = weight; j > 0; --j)
		{
			if (j >= items[i - 1][0])
			{
				dp0[j] = std::max(dp0[j],
								  dp0[j - items[i - 1][0]] + items[i - 1][1]);
			}
			else
			{
				dp0[j] = dp0[j];
			}
		}
	}

	return dp0[weight];
}

int main(int argc, char **argv)
{
	init();
//	std::cout << dp_res(0, W) << std::endl;
//	std::cout << exhaustion(0, W) << std::endl;
//	std::cout << dp_func(0, W) << std::endl;
	std::cout << dp_func2(n, W) << std::endl;
	std::cout << dp_func3(n, W) << std::endl;
}
