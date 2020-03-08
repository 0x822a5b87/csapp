#include <vector>
#include <queue>
#include "iostream"

/*
 * first 是到达该点的最短距离，second 是顶点
 */
typedef std::pair<int, int> P;

struct edge{ int to, cost; };

const int INF = 0xfffffff;

int V, E;

// 图的邻接表表示形式
std::vector<std::vector<edge> > G;
// 当前所有可以选择的顶点中最短路径或者次短路径
std::priority_queue<P, std::vector<P>, std::greater<P> > Q;

std::vector<int> dist0;
std::vector<int> dist1;

void init()
{
	std::cin >> V >> E;
	dist0.resize(V);
	dist1.resize(V);
	std::fill(dist0.begin(), dist0.end(), INF);
	std::fill(dist1.begin(), dist1.end(), INF);
	Q.push(P(0, 0));

	G.resize(V);
	int from, to, cost;
	for (int i = 0; i < E; ++i)
	{
		std::cin >> from >> to >> cost;
		from = from - 1;
		to = to - 1;
		edge e1;
		e1.to = to;
		e1.cost = cost;
		G[from].push_back(e1);
		edge e2;
		e2.to = from;
		e2.cost = cost;
		G[to].push_back(e2);
	}
}

void solve()
{
	while (!Q.empty())
	{
		P p = Q.top();
		Q.pop();
		int v = p.second, d = p.first;
		for (int u = 0; u < G[v].size(); ++u)
		{
			edge e = G[v][u];
			/*
			 * 从优先队列取出的数据，有可能是以下两项中的一项：
			 * 	1. 到达 v 的最短距离
			 * 	2. 到达 v 的次短距离
			 */
			int d2 = d + e.cost;

			/*
			 * 如果 d2 < dist0[e.to]，那么更新最短距离，并且之前的最短距离可能就是现在的次短距离
			 */
			if (d2 < dist0[e.to])
			{
				std::swap(dist0[e.to], d2);
				Q.push(P(dist0[e.to], e.to));
			}

			/*
			 * 更新次短距离
			 */
			if (d2 < dist1[e.to] && d2 > dist0[e.to])
			{
				dist1[e.to] = d2;
				Q.push(P(dist1[e.to], e.to));
			}
		}
	}

	std::cout << dist1[V - 1] << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}