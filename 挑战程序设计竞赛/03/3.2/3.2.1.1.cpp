#include "iostream"

const int MAX_LEN = 100;

int n, s;
int a[MAX_LEN], sum[MAX_LEN + 1];

void init()
{
	std::cin >> n >> s;

	for (int i = 0; i < n; ++i)
	{
		std::cin >> a[i];
	}
}

void solve()
{
	std::fill(sum, sum + n, 0);

	// sum[i] 是区间 [0, i) 的序列之和
	// sum[ub] - sub[lb] 是区间 (lb, ub] 的序列之和
	for (int i = 0; i < n; ++i)
	{
		sum[i + 1] += sum[i] + a[i];
	}

	// 如果不存在解
	if (sum[n] < s)
	{
		std::cout << "0" << std::endl;
		return;
	}

	int res = n;
	for (int start = 0; sum[start] + s <= sum[n]; ++start)
	{
		// t 是找到的数组下界的索引
		// 因为我们要求的是序列 [start, x) 这个区间的值，所以下界的值应该是 sum[start] + s
		int t = std::lower_bound(sum + start, sum + n, sum[start] + s) - sum;
		res = std::min(res, t - start);
	}

	std::cout << res << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();

	return 0;
}