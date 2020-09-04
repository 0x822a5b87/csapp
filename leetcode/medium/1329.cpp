//
// Created by 0x822a5b87 on 2020/8/27.
//
// 思路就是，把所有的对角线中的值取出来放到 vector 中，排好序之后放回去
// 实际上，我们的对角线有一个规律，就是对角线上的所有的点的坐标 (i - j) 相等

#include "iostream"
#include "vector"
#include "unordered_map"

using namespace std;

class Solution
{
public:
	vector<vector<int>> diagonalSort(vector<vector<int>> &mat)
	{
		unordered_map<int, vector<int>> um;

		for (size_t i = 0; i < mat.size(); ++i)
		{
			for (size_t j = 0; j < mat[i].size(); ++j)
			{
				um[i - j].emplace_back(mat[i][j]);
			}
		}

		for (auto &v : um)
		{
			std::sort(std::begin(v.second), std::end(v.second));
		}

		for (auto &pair : um)
		{
			int         diff = pair.first;
			vector<int> v    = pair.second;
			for (int    i    = 0; i < v.size(); ++i)
			{
				if (diff >= 0)
				{
					mat[diff + i][i] = v[i];
				}
				else
				{
					mat[i][i - diff] = v[i];
				}
			}
		}

		return mat;
	}
};

int main(int argc, char **argv)
{
	Solution            solution;
	vector<vector<int>> v{{3, 3, 1, 1},
						  {2, 2, 1, 2},
						  {1, 1, 1, 2}};
	// 0 -1 -2 -3
	// 1  0 -1 -2
	// 2  1  0 -1
	solution.diagonalSort(v);
	for (const auto &vs : v)
	{
		for (const auto num : vs)
		{
			std::cout << num << " ";
		}
		std::cout << std::endl;
	}
}