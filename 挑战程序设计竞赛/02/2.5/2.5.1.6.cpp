#include "iostream"

#define INF   0xffff
#define MAX_V 1024
#define MAX_E 1024

/* cost[u][v] 表示边 e = (u, v) 的权值 */
int cost[MAX_V][MAX_V];
int d[MAX_V];
int used[MAX_V];

int V, E;

void init()
{
	std::cin >> V >> E;
	std::fill(d, d + V, INF);
	std::fill(used, used + V, false);
	d[0] = 0;
	for (int u = 0; u < MAX_V; ++u)
	{
		for (int v = 0; v < MAX_V; ++v)
		{
			cost[u][v] = -1;
		}
	}

	char u, v;
	int c;
	for (int i = 0; i < E; ++i)
	{
		/* BUG：之前初始化只初始化了 cost[u][v]，然而这是一个无向图 */
		std::cin >> u >> v >> c;
		cost[u - 'a'][v - 'a'] = c;
		cost[v - 'a'][u - 'a'] = c;
	}
}

void dijkstra()
{
	while (true)
	{
		int v = -1;
		/*
		 * 首先从尚未使用过的顶点中选择一个距离最小的顶点。
		 *
		 * 这里注意我们使用的技巧，我们使用了 !used[u] 保证我们只查看未计算过的点
		 * 使用 v == -1 || d[u] < d[v] 来保证两个事情：
		 * 	1. 是否能够找到一个未计算过并且距离最小的顶点
		 * 	2. 如果我们能找到一个未计算过并且距离最小的顶点，那么 v 就是这个顶点的值
		 */
		for (int u = 0; u < V; ++u)
		{
			if (!used[u] && (v == -1 || d[u] < d[v]))
				v = u;
		}

		if (v == -1)
		{
			break;
		}

		used[v] = true;

		/*
		 * 此时，我们完成了一个新的顶点，并且这个顶点的 d[u] 就是起点到顶点u的最短路径；
		 * 那么，我们用从顶点 u 到下一个顶点的距离来更新最短路径
		 */
		for (int u = 0; u < V; u++)
		{
			/* 注意，这里一定要做这个判断。当 cost[v][u] < 0 时表示没有对应的路径 */
			if (cost[v][u] >= 0)
			{
				d[u] = std::min(d[u], d[v] + cost[v][u]);
			}
		}
	}


	for (int i = 0; i < V; ++i)
	{
		if (i != 0)
		{
			std::cout << ",";
		}
		std::cout << d[i];
	}
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	init();
	dijkstra();
}
