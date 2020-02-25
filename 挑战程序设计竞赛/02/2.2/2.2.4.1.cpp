#include "iostream"
#include "vector"
#include "algorithm"

void solve(std::vector<int> &arr, const int r)
{
	std::sort(arr.begin(), arr.end());
	int i = 0, ans = 0, N = arr.size();

	/**
	 * 每次循环中：
	 * 1. 找到第一个和起始点间距超过 r 的点，这个点的前一个点就是我们要找的中间节点
	 * 2. 从中间节点向后遍历，找到第一个和中间节点间距超过 r 的节点，这个节点就是下一次循环的起点
	 */
	while (i < N)
	{
		/**
		 * 不需要考虑 arr[0] > r
		 * 只需要考虑，arr[1] - arr[0] > r
		 * 如果成立，那么我们需要标记 arr[0]
		 */
		int s = arr[i++];
		while (i < N && arr[i] <= s + r)
			i++;
		/*
		 * 设置中间的 point，这个 point 到 arr[0] <= r
		 */
		int p = arr[i - 1];

		/**
		 * 找到第一个 arr[i] - p > r 的，这个点就是新的起始位置
		 */
		while (i < N && arr[i] <= p + r)
			i++;

		ans++;
	}

	if (ans != 0)
	{
		std::cout << ans << std::endl;
	}
}

int main(int argc, char **argv)
{
	int              r = 0, n = 0, cnt = 0, point;
	std::vector<int> arr;
	while (r != -1 || n != -1)
	{
		std::cin >> r >> n;
		// 为了方便计算
		while (cnt++ < n)
		{
			std::cin >> point;
			arr.push_back(point);
		}

		solve(arr, r);

		cnt = 0;
		arr.clear();
	}
}