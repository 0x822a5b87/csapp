#include "iostream"
#include "vector"

std::vector<std::vector<int > > G;
std::vector<int > color;

int vn, en;

void init()
{
	std::cin >> vn >> en;
	for (size_t i = 0; i < vn; ++i)
	{
		std::vector<int > v;
		G.push_back(v);
	}

	int from, to;
	for (size_t i = 0; i < en; ++i)
	{
		std::cin >> from >> to;
		G[from].push_back(to);
	}

	for (size_t i = 0; i < vn; ++i)
	{
		color.push_back(0);
	}
}

bool dfs(int v, int c)
{
	color[v] = c;
	for (int i : G[v])
	{
		/* 如果相邻的染色和该顶点一样，那么返回 false */
		if (color[i] == c)
			return false;

		/* 如果相邻的顶点还未被染色，那么染色成 -c */
		if (color[i] == 0 && !dfs(i, -c))
			return false;
	}
	return true;
}

void solve()
{
	for (size_t i = 0; i < vn; ++i)
	{
		if (color[i] == 0)
		{
			if (!dfs(i, 1))
			{
				std::cout << "No" << std::endl;
				return;
			}
		}
	}

	std::cout << "Yes" << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}
