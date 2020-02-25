#include "iostream"

// 2.1.4 深度优先搜索(DFS, Depth-First Search)

bool dfs(int *arr, size_t len, size_t i, int sum)
{
	if (sum == 0)
	{
		return true;
	}
	if (i >= len)
	{
		return false;
	}

	if (arr[i] > sum)
	{
		return dfs(arr, len, i + 1, sum);
	}

	return dfs(arr, len, i + 1, sum - arr[i]) | dfs(arr, len, i + 1, sum);
}

bool dfs(int *arr, size_t len, int sum)
{
	return dfs(arr, len, 0, sum);
}

int main(int argc, char **argv)
{
	int n;
	std::cin >> n;
	int arr[n];
	for (size_t i = 0; i < n; ++i)
	{
		std::cin >> arr[i];
	}
	int sum;
	std::cin >> sum;
	std::cout << (dfs(arr, n, sum) ? "Yes" : "No") << std::endl;
}