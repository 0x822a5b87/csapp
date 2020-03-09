#include "iostream"

typedef long long ll;

const ll MAX_N = 1e6 + 1;
const ll MAX_SQRT_N = 1e6 + 1;

bool isprime(int num)
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

bool is_prime[MAX_N];
bool is_prime_small[MAX_SQRT_N];

void segment_sieve(ll from, ll to)
{
	for (ll i = 0; i * i < to; i++)
		is_prime_small[i] = true;
	for (ll i = 0; i < to - from; ++i)
		is_prime[i] = true;
	for (ll i = 2; i * i < to; i++)
	{
		if (is_prime_small[i])
		{
			for (ll j = 2 * i; j * j < to; j += i)
			{
				is_prime_small[j] = false;
			}
			for (ll j = std::max(2LL, (from + i - 1) / i) * i; j < to; j += i)
			{
				is_prime_small[j - from] = false;
			}
		}
	}

	int res = 0;
	for (ll i = 2; i < MAX_SQRT_N; ++i)
	{
		if (is_prime_small[res])
			res++;
	}
	std::cout << res << std::endl;
}

int main(int argc, char **argv)
{
    ll from, to;
    std::cin >> from >> to;
	segment_sieve(from, to);
}