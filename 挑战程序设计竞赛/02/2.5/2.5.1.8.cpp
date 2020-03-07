#include "iostream"
#include "vector"

const int INF = 0xffff;

int V, E;

std::vector<std::vector<int> > d;

void init()
{
	std::cin >> V >> E;

	char from, to;
	int cost;

	for (int i = 0; i < E; ++i)
	{
		std::vector<int> v;
		for (int j = 0; j < E; ++j)
		{
			if (j == i)
				v.push_back(0);
			else
				v.push_back(INF);
		}
		d.push_back(v);
	}


	for (int i = 0; i < E; ++i)
	{
		std::cin >> from >> to >> cost;
		int f = from - 'a';
		int t = to - 'a';
		d[f][t] = cost;
		d[t][f] = cost;
	}
}

void floyd_warshall()
{
	for (int k = 0; k < V; ++k)
	{
		for (int u = 0; u < V; ++u)
		{
			for (int v = 0; v < V; ++v)
			{
				d[u][v] = std::min(d[u][v], d[u][k] + d[k][v]);
			}
		}
	}

	for (int i = 0; i < V; ++i)
	{
		for (int j = 0; j < V; ++j)
		{
			if (j != 0)
				std::cout << ",";

			std::cout << d[i][j];
		}
		std::cout << std::endl;
	}
}

int main(int argc, char **argv)
{
	init();
	floyd_warshall();
}