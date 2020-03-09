#include "iostream"
#include "vector"

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

/*
 * 约数枚举
 */
std::vector<int> divisor(int n)
{
	std::vector<int > res;
	int i;
	for (i = 1; i * i < n; ++i)
	{
		if (n % i == 0)
		{
			res.push_back(i);
			// 如果循环条件包含 i * i == n，那么需要判断 i * i 是否等于 n
			res.push_back(n / i);
		}
	}

	if (i * i == n)
	{
		res.push_back(i);
	}

	return res;
}