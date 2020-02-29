#include "iostream"
#include "limits"

#define MAX_N 1001

int n, arr[MAX_N];;

void init()
{
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> arr[i];
	}

	std::cout << " n = " << n << std::endl;
}

int solve()
{
	int dp[n];
	dp[0] = 1;

	for (int i = 1; i < n; ++i)
	{
		int max = 1;
		// 4 2 3 1 5
		for (int j = 0; j < i; ++j)
		{
			if (arr[i] > arr[j] && dp[j] >= max)
			{
				max = dp[j] + 1;
			}
		}
		dp[i] = max;
	}

	// BUG：我之前直接返回了 dp[n - 1]
	int max = 0;
	for (int i = 0; i < n; ++i)
	{
		if (dp[i] > max)
			max = dp[i];
	}
	return max;
}

long solve2()
{
	int dp[n];
	std::fill(dp, dp + n, INT_MAX);
	for (int i = 0; i < n; ++i)
		*std::lower_bound(dp, dp + n, arr[i]) = arr[i];

	return std::lower_bound(dp, dp + n, INT_MAX) - dp;
}

int main(int argc, char **argv)
{
	init();
	std::cout << solve() << std::endl;
	std::cout << solve2() << std::endl;
}
