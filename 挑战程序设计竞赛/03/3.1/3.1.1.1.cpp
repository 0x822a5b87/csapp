//
// Created by 0x822a5b87 on 2020/7/10.
//

#include "iostream"

int n, a[100], k;

void init()
{
	std::cin >> n;
	for (size_t i = 0; i < n; ++i)
	{
		std::cin >> a[i];
	}
	std::cin >> k;
}

void solve()
{
	if (n <= 0)
		return;

	int ret = n;
	int b   = 0, e = n - 1;
	while (e - b > 1)
	{
		int mid = (e + b) / 2;
		std::cout << 0 << " " << e << std::endl;
		if (a[mid] >= k)
		{
			e   = mid;
			ret = mid;
		}
		else
		{
			b = mid;
		}
	}

	std::cout << ret << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}