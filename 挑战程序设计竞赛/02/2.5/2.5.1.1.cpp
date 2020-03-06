#include "vector"
#include "iostream"

/**
 * 对于边有属性的情况
 *
 * struct edge { int to, cost; };
 * std::vector<std::vector<edge > > G;
 *
 * 3 3				顶点数和边数
 * 0 1				0 到 1 的边
 * 0 2				0 到 2 的边
 * 1 2				1 到 2 的边
 */

std::vector<std::vector<int > > G;

void init()
{
	int vk, ek;

	std::cin >> vk >> ek;

	for (size_t i = 0; i < vk; ++i)
	{
		G.push_back(std::vector<int>());
	}

	int from, to;

	for (size_t i = 0; i < ek; ++i)
	{
		std::cin >> from >> to;
		G[from].push_back(to);
	}
}

int main(int argc, char **argv)
{
	init();

	for (size_t i = 0; i < G.size(); ++i)
	{
		std::cout << i << ": " ;
		for (size_t j = 0; j < G[i].size(); ++j)
		{
			std::cout << G[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
