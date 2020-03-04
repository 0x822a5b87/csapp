#include "iostream"
#include "2.4.2.5.cpp"

#define N 100

int n, k;

int type[N];
int x[N];
int y[N];

void init2()
{
	std::cin >> n >> k;
	for (size_t i = 0; i < k; ++i)
	{
		std::cin >> type[i] >> x[i] >> y[i];
	}
}

int solve()
{
	int ans = 0;
	for (int i = 0; i < k; ++i)
	{
		int t = type[i];
		int x0 = x[i] - 1, y0 = y[i] - 1;
		if (x0 < 0 || x0 >= N || y0 < 0 || y0 >= N)
		{
			ans++;
			continue;
		}
		if (t == 1)
		{
			// 如果 xa 等于 yb 或者 yc，那么两个就不是同一个物种
			if (same(x0, y0 + k) || same(x0, y0 + 2 * k))
			{
				ans++;
			}
			else
			{
				unite(x0, y0);
				unite(x0 + k, y0 + k);
				unite(x0 + 2 * k, y0 + 2 * k);
			}
		}
		else if (type[i] == 2)
		{
			if (same(x0, y0) || same(x0, y0 + 2 * k))
			{
				ans++;
			}
			else
			{
				unite(x0, y0 + k);
				unite(x0 + k, y0 + 2 * k);
				unite(x0 + 2 * k, y0);
			}
		}
	}
	return ans;
}

int main(int argc, char **argv)
{
	init();
	init2();
	std::cout << solve() << std::endl;
}