#include <vector>
#include "iostream"

int              n;
std::vector<int> v1, v2, v3, v4;

void insert_v(std::vector<int> &v)
{
	int      value;
	for (int j = 0; j < n; ++j)
	{
		std::cin >> value;
		v.push_back(value);
	}
}

void init()
{
	std::cin >> n;
	insert_v(v1);
	insert_v(v2);
	insert_v(v3);
	insert_v(v4);
}

void solve()
{
	std::vector<int> cd;
	std::for_each(std::begin(v3), std::end(v3), [&cd](const int c)
	{
		std::for_each(std::begin(v4), std::end(v4), [&cd, &c](const int d)
		{
			cd.push_back(c + d);
		});
	});
	std::sort(std::begin(cd), std::end(cd));

	int count = 0;
	std::for_each(std::begin(v1), std::end(v1), [&cd, &count](const int a)
	{
		std::for_each(std::begin(v2), std::end(v2), [&cd, &a, &count](const int b)
		{
			count += std::upper_bound(std::begin(cd), std::end(cd), -(a + b))
					 - std::lower_bound(std::begin(cd), std::end(cd), -(a + b));
		});
	});

	std::cout << count << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}
