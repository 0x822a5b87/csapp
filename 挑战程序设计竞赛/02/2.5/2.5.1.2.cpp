#include "iostream"
#include "vector"

struct vertex
{
	/**
	 * 顶点的其他属性
	 */
	 int to;
	 int cost;
};

std::vector<std::vector<vertex> > G;


void init()
{
	int vk, ek;

	std::cin >> vk >> ek;

	for (size_t i = 0; i < vk; ++i)
	{
		G.push_back(std::vector<vertex>());
	}

	int from, to, cost;

	for (size_t i = 0; i < ek; ++i)
	{
		std::cin >> from >> to >> cost;
		struct vertex v = {to, cost};
		G[from].push_back(v);
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
			if (j != 0)
			{
				std::cout << ", ";
			}
			std::cout << "[" << G[i][j].to
					  << "," << G[i][j].cost << "]";
		}
		std::cout << std::endl;
	}
}
