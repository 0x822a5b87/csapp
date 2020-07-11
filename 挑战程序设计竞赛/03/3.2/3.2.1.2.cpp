#include "iostream"

const int MAX_LEN = 100;

int n, s;
int a[MAX_LEN];

void init()
{
	std::cin >> n >> s;

	for (int i = 0; i < n; ++i)
	{
		std::cin >> a[i];
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

void solve()
{
	int ret = n + 1;
	for (int start = 0, cur = 0, sum = 0; cur < n; ++cur)
	{
		// 计算 [start, cur] 的序列和
		sum += a[cur];
		if (sum >= s)
		{
			// 当 [start, cur] 的序列和大于等于s时，我们需要减去那些不必要的部分
			while (sum >= s)
			{
				sum -= a[start++];
			}
			// 这个时候 [start - 1, cur] 是满足条件的序列，所以它的长度是 cur - start + 2
			ret = std::min(ret, cur - start + 2);

			// 注意，这个时候：sum = sum([start, end])
			// 在下一次循环的时候我们就需要计算 sum = sum([start, end + 1]) 了
		}
	}
	std::cout << ret << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
	return 0;
}