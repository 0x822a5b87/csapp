#include "iostream"

typedef long long ll;

ll pow(ll x, ll n)
{
	ll res = 1;
	while (n > 0)
	{
		if (n & 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return res;
}

ll mod_pow(ll x, ll n, ll mod)
{
	ll res = 1;
	while (n > 0)
	{
		if (n & 1)
			res = res * x % mod;

		x = x * x % mod;
		n >>= 1;
	}
	return res;
}

int main(int argc, char **argv)
{
	int num;
	std::cin >> num;
	bool t = true;
	for (int i = 2; i < num; ++i)
	{
		if (mod_pow(i, num, num) != (i % num))
		{
			std::cout << i << std::endl;
			t = false;
			break;
		}
	}
	std::cout << (t ? "Yes" : "No") << std::endl;
}