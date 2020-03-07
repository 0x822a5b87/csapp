#include "iostream"
#include "queue"

const size_t MAX_V = 1024;

class edge
{
public:
	int from, to, cost;

	edge(int from, int to, int cost) : from(from), to(to), cost(cost)
	{}
};

struct EdgeCompare
{
	bool operator()(const edge &lhs, const edge &rhs)
	{
		return lhs.cost > rhs.cost;
	}
};

int V, E;

bool used[MAX_V];
std::vector<std::vector<edge> > G;
std::priority_queue<edge, std::vector<edge>, EdgeCompare> q;

void init()
{
	std::cin >> V >> E;
	char from, to;
	int cost;
	G.resize(V);
	for (int i = 0; i < E; ++i)
	{
		std::cin >> from >> to >> cost;
		int f = from - 'a';
		int t = to - 'a';
		G[f].push_back(edge(f, t, cost));
		G[t].push_back(edge(t, f, cost));
	}
	memset(used, 0, sizeof(used));

	for (int i = 0; i < G[0].size(); ++i)
	{
		q.push(G[0][i]);
	}

	used[0] = true;
}

void prim()
{
	int mst = 0;
	while (!q.empty())
	{
		const edge e0 = q.top();
		q.pop();
		if (used[e0.from] && !used[e0.to])
		{
			used[e0.to] = true;
			mst += e0.cost;
			for (int i = 0; i < G[e0.to].size(); ++i)
			{
				q.push(G[e0.to][i]);
			}
			std::cout << e0.from << " " << e0.to << " " << e0.cost << std::endl;
		}
	}
	std::cout << mst << std::endl;
}

int main(int argc, char **argv)
{
	init();
	prim();
}