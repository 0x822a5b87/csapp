//
// Created by 0x822a5b87 on 2020/8/27.
//

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	vector<vector<int>> generateMatrix(int n)
	{
		vector<vector<int>> v;
		v.resize(n);
		for (auto &sv : v)
		{
			sv.resize(n);
		}
		int powN = n * n;
		int lb = 0, rb = n - 1, ub = 0, db = n - 1;
		for (size_t i = 1; i <= powN; )
		{
			for (int j = lb; j <= rb && i <= powN; ++j, ++i)
			{
				v[ub][j] = i;
			}
			for (int j = ub + 1; j < db && i <= powN; ++j, ++i)
			{
				v[j][rb] = i;
			}
			for (int j = rb; j >= lb && i <= powN; --j, ++i)
			{
				v[rb][j] = i;
			}
			for (int j = db - 1; j > ub && i <= powN; --j, ++i)
			{
				v[j][lb] = i;
			}
			++lb;
			--rb;
			++ub;
			--db;
		}
		return v;
	}
};

int main(int argc, char **argv)
{
	Solution solution;
	const vector<vector<int>> &v = solution.generateMatrix(3);

	for (const auto& sv : v)
	{
		for (const auto n : sv)
		{
			std::cout << n << " ";
		}
		std::cout << std::endl;
	}
}