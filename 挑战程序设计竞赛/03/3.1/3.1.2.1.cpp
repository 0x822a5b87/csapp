#include <cmath>
#include "iostream"

// 解题思路
// 假设切割之后每条绳子的长度为 x，那么每条绳子的可以被切割的数量是 n[i] = floor(L[i] / x)
// 那么所有绳子被切割的总长度就是 n[0] + ... n[size - 1]，只要这个数字大于 K 说明满足条件
// 那么我们现在应该存在一个数组，当数组中

int n, k;
double len[100];

void init()
{
	std::cin >> n;
	std::cin >> k;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> len[i];
	}
}

bool C(double x)
{
	int num = 0;
	for (int i = 0; i < n; ++i)
	{
		num += static_cast<int>(len[i]) / x;
	}
	return num >= k;
}

double max_len()
{
	double max = 0;
	for (size_t i = 0; i < n; ++i)
	{
		if (len[i] > max)
		{
			max = len[i];
		}
	}
	return max;
}

void solve()
{
	double lb = 0, ub = max_len() + 1;
	for (int i = 0; i < 100; ++i)
	{
		double mid = (lb + ub) / 2;
		if (C(mid))
		{
			lb = mid;
		}
		else
		{
			ub = mid;
		}
	}
	printf("%.2f\n", floor(ub * 100) / 100);
}

int main(int argc, char **argv)
{
	init();
	solve();
}