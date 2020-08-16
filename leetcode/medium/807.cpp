//
// Created by 0x822a5b87 on 2020/8/14.
//

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	int maxIncreaseKeepingSkyline(vector<vector<int>> &grid)
	{
		if (grid.empty())
		{
			return 0;
		}
		vector<int> left(grid.size());
		vector<int> up(grid[0].size());
		for (size_t i = 0; i < grid.size(); ++i)
		{
			for (size_t j = 0; j < grid[i].size(); ++j)
			{
				// grid[i][j] 需要更新 left[i] 和 vertical[j]
				left[i] = std::max(left[i], grid[i][j]);
				up[j]   = std::max(up[j], grid[i][j]);
			}
		}

		int sum = 0;
		for (size_t i = 0; i < grid.size(); ++i)
		{
			for (size_t j = 0; j < grid[i].size(); ++j)
			{
				// grid[i] 的最大高度取决于 left[i] 和 up[j]
				int max = std::min(left[i], up[j]);
				sum += max - grid[i][j];
			}
		}

		return sum;
	}
};

int main(int argc, char **argv)
{
	std::vector<std::vector<int>> v{
			{3, 0, 8, 4},
			{2, 4, 5, 7},
			{9, 2, 6, 3},
			{0, 3, 1, 0}
	};

	Solution s;
	std::cout << s.maxIncreaseKeepingSkyline(v) << std::endl;
}