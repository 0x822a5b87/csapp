#include "iostream"

int n, k;
double w_v[100][2];
double per_w[100];

void init()
{
	std::cin >> n >> k;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> w_v[i][0] >> w_v[i][1];
	}
}

bool judge(double x)
{
	for (int i = 0; i < n; ++i)
	{
		per_w[i] = w_v[i][1] - x * w_v[i][0];
	}
	std::sort(per_w, per_w + n);

	double sum = 0;
	for (int i = 0; i < k; ++i)
	{
		sum += per_w[n - i - 1];
	}

	return sum > 0;
}

void solve()
{
	// 计算100次
	double lb = 0, ub = 10e6;
	for (int i = 0; i < 100; ++i)
	{
		double mid = (lb + ub) / 2;
		if (judge(mid))
		{
			lb = mid;
		}
		else
		{
			ub = mid;
		}
	}

	printf("%.2f\n", lb);
}

int main(int argc, char **argv)
{
	init();
	solve();

	return 0;
}