#include "iostream"

#define INF 10000000

const int MAX_N = 15;

int c, n;
int d[MAX_N][MAX_N];

// 假设 i 是所有已经到达的顶点的集合，j 是当前顶点
// value 是从顶点 j 到达所有未达到顶点之后回到起点0的最短路径
// dp[i][j] = 0									i == (1u << MAX_N) - 1;
// dp[i][j] = ?
// 对于上面的递推公式来说，我们从 j 开始可以达到的所有可达顶点（所有有路径并且尚未去过的顶点）
// 我们先假设走向任意可达顶点 v，随后加上 dp[u][v]，其中 u 是 i 新达到顶点 v 的并集
// dp[u][v] + dp[i][v] 就是经过 j 可以回到原点的最短路径
// 如果我们尝试所有的可达顶点，并求出最小值，这个最小值就是 dp[i][j] 可回到原点的最小值。
int dp[1u << MAX_N][MAX_N];

void init()
{
	std::cin >> c;
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			d[i][j] = -1;
		}
	}

	int from, to, cost;

	for (int i = 0; i < n; ++i)
	{
		std::cin >> from >> to >> cost;
		d[from][to] = cost;
	}

	memset(dp, -1, sizeof(dp));
}

int rec(int S, int v)
{
	// 如果 dp[S][v] >= 0，说明这个结果已经计算过了
	if (dp[S][v] >= 0)
	{
		return dp[S][v];
	}

	// 所有的顶点都已经到达过了，并且已经回到了0号节点
	if (S == (1u << c) - 1 && v == 0)
	{
		return dp[S][v] = 0;
	}

	int      res = INF;
	// n 个节点，每个节点都计算一下经过它达到原点的最短路径
	for (int u   = 0; u < c; u++)
	{
		// 如果这个节点还没有到达过，并且包含一条从 v 到 u 的路径
		if (!((S >> u) & 1u) && d[v][u] >= 0)
		{
			res = std::min(rec(S | (1u << u), u) + d[v][u], res);
		}
	}
	return dp[S][v] = res;
}

void solve()
{
	std::cout << rec(0, 0) << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}