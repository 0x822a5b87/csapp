// 邻接表实现

#include <vector>
#include "iostream"

const int MAX_V = 1024;
const int INF = 100000;

struct edge
{
	// 终点，容量，反向边
	int to, cap, rev;
};

int               n;
// 图的邻接表
std::vector<edge> G[MAX_V];
// 深度优先搜索中的节点是否到达的表示
bool              used[MAX_V];

// 向图中增加一条从 s 到 t，容量为 cap 的边
// 注意，这里初始化 from 到 to 时，把 from -> to 和 to -> from 都认为是反向边
// 并且 from -> to 的初始容量为 cap, to -> from 的初始容量为 0
// 当我们的 dfs 从 from 走到 to 时，
// from -> to 的容量减去实际流量
// to -> from 的容量加上实际流量
// 通过这种优化手段我们可以很方便的去处理数据的所有链路
void add_edge(int from, int to, int cap)
{
	// G[from] 的反向边等于 G[to][G[to].size()]
	G[from].push_back(edge{to, cap, static_cast<int >(G[to].size())});
	G[to].push_back(edge{from, 0, static_cast<int >(G[to].size()) - 1});
}

int dfs(int v, int t, int f)
{
	// 如果已经到达终点
	if (v == t)
	{
		return f;
	}
	used[v] = true;
	// 搜索每一条边
	for (int i = 0; i < G[v].size(); ++i)
	{
		edge &e = G[v][i];
		if (!used[e.to] && e.cap > 0)
		{
			// 实际流量是深度优先搜索中最小的那一条边的容量
			int d = dfs(e.to, t, std::min(f, e.cap));
			if (d > 0)
			{
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

void init()
{
	std::cin >> n;
	int      from, to, cap;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> from >> to >> cap;
		add_edge(from, to, cap);
	}
}

int max_flow(int s, int t)
{
	int flow = 0;
	for (;;)
	{
		memset(used, 0, sizeof(used));
		int f = dfs(s, t, INF);
		// 从 s 开始深度优先搜索已经找不到任何路径了
		if (f == 0)
		{
			return flow;
		}
		flow += f;
	}
}

int main(int argc, char **argv)
{
	init();
	std::cout << max_flow(0, 4) << std::endl;
}