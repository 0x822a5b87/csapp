// 树状数组

#include <vector>
#include "iostream"

int n;
std::vector<int> a, c;

size_t low_bit(size_t x)
{
	return x & (-x);
}

int get_sum(size_t x)
{
	int s = 0;
	while (x > 0)
	{
		s += c[x];
		x -= low_bit(x);
	}
	return s;
}

void add(size_t x, int v)
{
	a[x] += v;
	while (x <= n)
	{
		c[x] += v;
		x += low_bit(x);
	}
}

void init()
{
	std::cin >> n;
	// 树状数组的下标是从 1 开始的
	a.resize(n + 1);
	c.resize(n + 1);
	for (int i = 1; i <= n; ++i)
	{
		a[i] = 0;
		c[i] = 0;
	}

	int num;
	for (int i = 1; i <= n; ++i)
	{
		std::cin >> num;
		add(i, num);
	}
}

int main(int argc, char **argv)
{
	init();

	assert(get_sum(1) == 1);
	assert(get_sum(2) == 3);
	assert(get_sum(3) == 6);
	assert(get_sum(4) == 10);
	assert(get_sum(5) == 15);
	assert(get_sum(6) == 21);
	assert(get_sum(7) == 28);
}