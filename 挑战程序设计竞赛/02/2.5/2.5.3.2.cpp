#include "iostream"
#include "queue"

const int MAX_V = 1024;

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

int par[MAX_V];
int rank[MAX_V];

static int find(int x);

void init()
{
	for (int i = 0; i < MAX_V; ++i)
	{
		par[i]  = i;
		rank[i] = 0;
	}
}

bool same(int m, int n)
{
	return find(m) == find(n);
}

void unite(int m, int n)
{
	m = find(m);
	n = find(n);
	if (m == n)
	{
		return;
	}
	if (rank[m] > rank[n])
	{
		par[n] = par[m];
	}
	else
	{
		par[m] = par[n];
		if (rank[m] == rank[n])
		{
			rank[m]++;
		}
	}
}

int V, E;
std::priority_queue<edge, std::vector<edge>, EdgeCompare> q;

void init2()
{
	init();
	std::cin >> V >> E;
	char from, to;
	int cost;
	for (int i = 0; i < E; ++i)
	{
		std::cin >> from >> to >> cost;
		int f = from - 'a';
		int t = to - 'a';
		q.push(edge(f, t, cost));
		q.push(edge(t, f, cost));
	}
}

void kruskal()
{
	int mst = 0;
	while (!q.empty())
	{
		edge e = q.top();
		if (!same(e.from, e.to))
		{
			mst += e.cost;
			unite(e.from, e.to);
			std::cout << e.from << " " << e.to << " " << e.cost << std::endl;
		}
		q.pop();
	}
	std::cout << mst << std::endl;
}

static int find(int x)
{
	if (par[x] == x)
	{
		return x;
	}
	return find(par[x]);
}

int main(int argc, char **argv)
{
	init2();
	kruskal();
}
