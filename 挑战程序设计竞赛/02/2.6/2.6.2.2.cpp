#include "iostream"

bool is_prime(int num)
{
	if (num == 1)
	{
		return false;
	}

	for (int i = 2; i * i <= num; ++i)
	{
		if (num % i == 0)
		{
			return false;
		}
	}

	return true;
}

void sieve(int n)
{
	int res = 0;
	/*
	 * 这里可以通过 bit a[n+1] 来优化空间，因为我们可以用索引表示数字
	 */
	int a[n + 1];
	for (int i = 1; i <= n; ++i)
	{
		a[i] = i;
	}

	for (int i = 2; i <= n; ++i)
	{
		if (is_prime(i))
			res++;
		for (int j = 1; i * j <= n; ++j)
		{
			a[i * j] = -1;
		}
	}

	std::cout << res << std::endl;
}

int main(int argc, char **argv)
{
	int x;
	std::cin >> x;
	sieve(x);
}