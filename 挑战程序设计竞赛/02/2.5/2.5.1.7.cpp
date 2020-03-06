#include <vector>
#include <queue>
#include "iostream"

typedef std::pair<int, int> P;

const int INF = 0xffff;

class edge
{
public:
	edge(int to, int cost) : to(to), cost(cost)
	{}

	int to, cost;
};

int V, E;

/*
 * first 是顶点，second 是最短距离。
 *
 * 我们使用堆来存储需要计算的路径，这样将找到需要计算的顶点的时间复杂度从 V 降低到 log(V)
 */
std::priority_queue<P, std::vector<P>, std::greater<P> > q;

std::vector<std::vector<edge> > G;

std::vector<int> d;

void dijkstra()
{
	while (!q.empty())
	{
		/* 找到需要计算的最短路径 */
		P p = q.top();
		q.pop();
		int u = p.first;
		/* 尝试更新从当前节点出发能到达的所有节点的路径 */
		for (size_t v = 0; v < G[u].size(); ++v)
		{
			edge &e = G[u][v];
			if (d[e.to] > d[u] + e.cost)
			{
				d[e.to] = d[u] + e.cost;
				q.push(std::make_pair(e.to, d[e.to]));
			}
		}

	}

	for (size_t i = 0; i < d.size(); ++i)
	{
		if (i != 0)
		{
			std::cout << ",";
		}
		std::cout << d[i];
	}
	std::cout << std::endl;
}

void init()
{
	std::cin >> V >> E;
	G.resize(V);
	q.push(std::make_pair(0, 0));
	d.resize(V);
	std::fill(d.begin(), d.end(), INF);
	d[0] = 0;
	char from, to;
	int cost;
	for (int u = 0; u < E; ++u)
	{
		std::cin >> from >> to >> cost;
		from = from - 'a';
		to = to - 'a';
		G[from].push_back(edge(to, cost));
		G[to].push_back(edge(from, cost));
	}

	std::cout << "V = " << V << std::endl;
	std::cout << "E = " << E << std::endl;
	std::cout << "G.size() = " << G.size() << std::endl;
}

int main(int argc, char **argv)
{
	init();
	dijkstra();
}