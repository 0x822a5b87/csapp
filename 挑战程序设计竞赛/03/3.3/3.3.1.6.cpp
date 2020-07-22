/**
 * 冒泡排序的交换次数
 */
#include <vector>
#include "iostream"

int n;
std::vector<int> a, c;

ssize_t low_bit(size_t x)
{
	return x & (-x);
}

void add(size_t x, int v)
{
	while (x <= n)
	{
		c[x] += v;
		x += low_bit(x);
	}
}

int get_sum(size_t x)
{
	int s = 0;
	while (x != 0)
	{
		s += c[x];
		x -= low_bit(x);
	}
	return s;
}

void init()
{
	std::cin >> n;
	a.resize(n + 1);
	c.resize(n + 1);
	for (int i = 0; i <= n; ++i)
	{
		a[i] = 0;
		c[i] = 0;
	}

	for (size_t i = 0; i <= n; ++i)
	{
		std::cin >> a[i];
	}
}

void solve()
{
	int ret = 0;
	for (int i = 0; i < n; ++i)
	{
		ret += i - get_sum(a[i]);
		add(a[i], 1);
	}
	std::cout << ret << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}