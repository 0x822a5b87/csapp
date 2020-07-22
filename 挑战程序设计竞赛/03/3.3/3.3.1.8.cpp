// 离散化测试

#include <vector>
#include "iostream"

struct node
{
	int v, order;
};

int               n;
std::vector<node> a;
std::vector<int> d;

void init()
{
	std::cin >> n;
	a.resize(n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> a[i].v;
		a[i].order = i;
	}

	std::sort(std::begin(a), std::end(a), [](const node &l, const node &r)
	{
		return l.v < r.v;
	});

	// 离散化映射
	d.resize(n);
	for (int i = 0; i < n; ++i)
	{
		d[a[i].order] = i;
	}
}

int main(int argc, char **argv)
{
	init();
}