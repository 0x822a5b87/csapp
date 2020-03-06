#include "iostream"

#define INF   0xFFFF
#define MAX_E 1024
#define MAX_V 1024

struct edge
{
	int from, to, cost;
};

/* 边 */
edge es[MAX_E];
/* 到顶点 i 的最短距离 */
int d[MAX_V];
int V, E;

bool find_negative_loop()
{
	memset(d, 0, sizeof(d));
	for (int i = 0; i < V; ++i)
	{
		for (int j = 0; j < E; ++j)
		{
			edge e = es[j];
			if (d[e.to] > d[e.from] + e.cost) {
				d[e.to] = d[e.from] + e.cost;
				if (i == V - 1)
					return true;
			}
		}
	}

	return false;
}

void shortest_path(int s)
{
	for (size_t i = 0; i < V; ++i)
		d[i] = INF;
	d[s] = 0;

	while (true)
	{
		bool update = false;
		/* 在每次 for 循环中遍历一次边 */
		for (size_t i = 0; i < E; i++)
		{
			edge e = es[i];
			/* 如果 d[e.from] != INF，说明该到达该顶点的最短路径已经更新 */
			/* 那么我们可以尝试用从 e.from 走到 e.to 这条路径与当前 d[e.to] 的最短路径比较 */
			if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost)
			{
				d[e.to] = d[e.from] + e.cost;
				update = true;
			}
		}
		if (!update)
			break;
	}
}
