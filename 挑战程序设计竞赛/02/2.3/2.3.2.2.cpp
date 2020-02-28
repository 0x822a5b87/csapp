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

/*
 * 定义 dp[i+1][j] 表示从前面 i 个物品中挑选出总价值为 j 的最小重量，不能满足则等于 INF，否则 >=0
 */
int solve(int max_num, int max_weight)
{
	// 100 表示每个物品的最大单价
	int dp[max_num + 1][max_num * 5 + 1];
	dp[0][0] = 0;
	for (int i = 1; i < max_num + 1; ++i)
		dp[i][0] = 0;
	for (int j = 1; j < max_num * 5 + 1; ++j)
		// 最早我的实现这里使用的是 -1 表示不可达到，但是在动态规划中我们需要选择 std::min
		// 所以 -1 需要额外的步骤去判断是重量小于，还是不论怎么选，都达不到这个价值
		dp[0][j] = 0xffff;

	for (int i = 1; i < max_num + 1; i++)
	{
		for (int j = 1; j < max_num * 5 + 1; ++j)
		{
			// 同样的错误：没有判断 j >= v[i - 1] 又犯了一次
			// 另外，没有对不满足条件时的 dp[i][j] 赋值又犯了一次
			if (j >= v[i - 1])
			{
				// 最开始我还是在使用 std::max
				dp[i][j] = std::min(dp[i - 1][j],
									dp[i - 1][j - v[i - 1]] + w[i - 1]);
			}
			else
			{
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	// 最开始我返回了 dp[max_num][i] 而不是索引，这其实是错误的
	for (int i = max_num * 5; i >= 0; --i)
	{
		if (dp[max_num][i] <= max_weight)
		{
			return i;
		}
	}

	return 0;
}

int main(int argc, char **argv)
{
	init();
	std::cout << solve(n, weight) << std::endl;
}
