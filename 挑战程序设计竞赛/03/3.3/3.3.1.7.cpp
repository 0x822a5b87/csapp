// 求逆序对 + 离散化
#include <vector>
#include "iostream"

struct node
{
	int v;
	int order;
};

int               n;

std::vector<int> a, c0;
// 离散化之后的数组
std::vector<int> d2;
std::vector<node> d;

ssize_t low_bit(size_t x)
{
	return x & (-x);
}

void add(size_t x, int v)
{
	while (x <= n)
	{
		c0[x] += v;
		x += low_bit(x);
	}
}

int get_sum(size_t x)
{
	int s = 0;
	while (x != 0)
	{
		s += c0[x];
		x -= low_bit(x);
	}
	return s;
}

void init()
{
	std::cin >> n;
	a.resize(n);
	d.resize(n);
	d2.resize(n);
	c0.resize(n + 1);
	for (int i = 0; i < n; ++i)
	{
		a[i] = 0;
		d[i] = {0, 0};
	}

	for (size_t i = 0; i < n; ++i)
	{
		std::cin >> a[i];
		d[i].v = a[i];
		d[i].order = i;
	}

	// 离散化数组
	std::sort(std::begin(d), std::end(d), [](const node &l, const node &r)
	{
		return l.v < r.v;
	});

	for (int i = 0; i < n; ++i)
	{
		d2[d[i].order] = i + 1;
	}
}

void solve()
{
	int      ret = 0;
	for (int i   = 0; i < n; ++i)
	{
		ret += i - get_sum(d2[i]);
		std::cout << i << std::endl;
		add(d2[i], 1);
	}
	std::cout << ret << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}