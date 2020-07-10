#include "iostream"

int n, m;
int x[100];

void init()
{
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> x[i];
	}
	// 注意，我们需要对数组排序，因为输入是无序的。
	std::sort(&x[0], &x[n-1]);
}

bool yes(int dis)
{
	int prev = -1000, remaining = m;
	for (int i = 0; i < n && remaining > 0; ++i)
	{
		if (x[i] - prev >= dis)
		{
			// 满足条件就放置一头牛
			--remaining;
			prev = x[i];
		}
	}

	return remaining == 0;
}

void solve()
{
	int lb = 0, ub = x[n - 1];
	while (ub - lb > 1)
	{
		int mid = (lb + ub) / 2;
		if (yes(mid))
		{
			lb = mid;
		}
		else
		{
			ub = mid;
		}
	}
	std::cout << lb << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}