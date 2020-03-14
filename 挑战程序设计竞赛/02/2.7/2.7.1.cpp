#include "iostream"

const int MaxN = 1024;

int num;

int v1[MaxN];
int v2[MaxN];

void init()
{
	std::cin >> num;
	for (int i = 0; i < num; ++i)
	{
		std::cin >> v1[i];
	}

	for (int i = 0; i < num; ++i)
	{
		std::cin >> v2[i];
	}
}

void solve()
{
	std::sort(v1, v1 + num);
	std::sort(v2, v2 + num);
	long long res = 0;
	for (int i = 0; i < num; ++i)
	{
		res += static_cast<long long>(v1[i])
			   * static_cast<long long>(v2[num - i - 1]);
	}

	std::cout << res << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}