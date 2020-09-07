//
// Created by 0x822a5b87 on 2020/9/4.
//

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	void rotate(vector<vector<int>> &matrix)
	{
		size_t n = matrix.size();
		size_t r = (n >> 1u) - 1u; //左上角区域的最大行下标，
		size_t c = (n - 1u) >> 1u; //左上角区域的最大列下标，行列下标从 0 开始。

		for (size_t i = 0; i <= r; ++i)
		{
			for (size_t j = 0; j <= c; ++j)
			{
				std::swap(matrix[i][j], matrix[j][n - i - 1]);
				std::swap(matrix[i][j], matrix[n - i - 1][n - j - 1]);
				std::swap(matrix[i][j], matrix[n - j - 1][i]);
			}
		}
	}
};

int main(int argc, char **argv)
{
	Solution solution;

	vector<vector<int>> matrix = {{1}};

	solution.rotate(matrix);

	return 0;
}