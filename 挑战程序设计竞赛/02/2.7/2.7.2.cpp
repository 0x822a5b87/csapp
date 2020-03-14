#include "iostream"

const int MaxN = 1024;

int N;
int M[MaxN][MaxN];

void init()
{
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cin >> M[i][j];
		}
	}
}

void solve()
{
	// 记录从右到左连续的 0 的个数
	int a[N];
	for (int i = 0; i < N; ++i)
	{
		int cnt = 0;
		for (int j = N - 1; j >= 0; --j)
		{
			if (M[i][j] == 0)
				++cnt;
			else
				break;
		}
		a[i] = cnt;
	}

	int res = 0;
	for (int i = N - 1; i >= 0; --i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (a[j] == -1)
			{
				continue;
			}
			else if (a[j] >= i)
			{
				a[j] = -1;
				break;
			}
			else
			{
				++res;
			}
		}
	}
	std::cout << res << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}