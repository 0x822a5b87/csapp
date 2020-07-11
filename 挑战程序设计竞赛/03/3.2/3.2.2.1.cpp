#include "iostream"

const int max_len = 5000;

int n;
int dir[max_len];
int f[max_len];

void init()
{
	std::cin >> n;
	char     tmp;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> tmp;
		dir[i] = tmp == 'F' ? 0 : 1;
		std::cout << dir[i] << " ";
	}
	std::cout << std::endl;
}

int cal(int k)
{
	std::fill(f, f + n, 0);

	int res = 0;
	// f 的和
	int sum = 0;
	// 这里必须是 <=
	for (int i = 0; i + k <= n; ++i)
	{
		if (((sum + dir[i]) % 2) != 0)
		{
			res += 1;
			f[i] = 1;
		}
		sum += f[i];
		if (i - k + 1 >= 0)
		{
			sum += f[i - k + 1];
		}
	}

	for (int i = n - k + 1; i < n; ++i)
	{
		if (((sum + dir[i]) % 2) != 0)
		{
			return -1;
		}
		if (i - k + 1 >= 0)
		{
			sum += f[i - k + 1];
		}
	}

	return res;
}

void solve()
{
	int K = 1, M = n;
	for (int k = 2; k <= n; ++k)
	{
		int m = cal(k);
		if (m > 0 && m < M)
		{
			K = k;
			M = m;
			std::cout << K << " " << M << std::endl;
		}
	}

	std::cout << "k = " << K << ", m = " << M << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();

	return 0;
}