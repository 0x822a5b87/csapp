#include <vector>
#include "iostream"

// 邻接矩阵的实现

const int MAX_N = 1024;
const int INF   = 100000;

int n;
std::vector<bool> used;
// 正向边
std::vector<std::vector<int> > g;
// 反向边
std::vector<std::vector<int> > r;

// 0 1 2 4
// 0 1 3 4
//
int dfs(int s, int t, int f, std::vector<int> path)
{
//	std::cout << s << " " << t << " " << f << std::endl;
	if (s == t)
	{
		std::cout << "f = " << f << std::endl;
		for (int i = 0; i < path.size(); ++i)
		{
			std::cout << path[i] << " ";
		}
		std::cout << std::endl;
		return f;
	}
	used[s] = true;
	// 这里就可以看出来为什么要使用邻接表而不是用邻接矩阵了
	// 因为需要遍历某个点的所有路径，所以使用邻接表会被邻接矩阵更快
	for (int i = 0; i <= t; ++i)
	{
		// 如果节点 i 没有经过
		if (!used[i])
		{
			// 如果找到了一条正向路径
			if (g[s][i] > 0)
			{
				// 继续深度搜索，并且修改实际流量
				path.push_back(i);
				int d = dfs(i, t, std::min(f, g[s][i]), path);
				if (d > 0)
				{
					g[s][i] -= d;
					r[i][s] += d;
					return d;
				} else {
					path.pop_back();
				}
			}
			// 找到了一条反向路径，
			else if (r[s][i] > 0)
			{
				path.push_back(i);
				// 继续深度搜索，并且修改实际流量
				int d = dfs(i, t, std::min(f, r[s][i]), path);
				if (d > 0)
				{
					g[s][i] += d;
					r[s][i] -= d;
					return d;
				} else {
					path.pop_back();
				}
			}
		}
	}
	return 0;
}

int max_flow(int s, int t)
{
	int flow = 0;
	while (true)
	{
		std::fill(std::begin(used), std::end(used), false);
		std::vector<int> v;
		int ret = dfs(s, t, INF, v);
		if (ret == 0)
		{
			return flow;
		}
		flow += ret;
	}
}

void init_graph(std::vector<std::vector<int>> &graph)
{
	graph.resize(MAX_N);
	for (auto &sub_graph : graph)
	{
		sub_graph.resize(MAX_N);
		for (auto &c : sub_graph)
		{
			c = -1;
		}
	}
}

void init()
{
	used.resize(MAX_N);
	init_graph(g);
	init_graph(r);
	std::cin >> n;
	int      from, to, cap;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> from >> to >> cap;
		g[from][to] = cap;
		// r 表示的是有一条从 to 到 from 的反向边
		r[to][from] = 0;
	}
}

int main(int argc, char **argv)
{
	init();
	std::cout << max_flow(0, 4) << std::endl;
}
