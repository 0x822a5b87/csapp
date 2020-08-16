//
// Created by 0x822a5b87 on 2020/8/15.
//

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	vector<vector<int>> groupThePeople(vector<int> &groupSizes)
	{
		vector<std::vector<int> > cache(500);
		vector<std::vector<int> > ret;

		for (size_t i = 0; i < groupSizes.size(); ++i)
		{
			vector<int> &group = cache[groupSizes[i]];
			group.emplace_back(i);
			if (group.size() == groupSizes[i])
			{
				ret.emplace_back(group);
				group.clear();
			}
		}

		return ret;
	}
};

class Solution2
{
public:
	vector<vector<int>> groupThePeople(vector<int> &g)
	{
		vector<vector<int>> v(500), ans;
		for (int            i = 0; i < g.size(); ++i)
		{
			v[g[i]].emplace_back(i);
			if (v[g[i]].size() == g[i])
			{
				ans.emplace_back(v[g[i]]);
				v[g[i]].clear();
			}
		}
		return ans;
	}
};

int main(int argc, char **argv)
{
	vector<int>               group{3, 3, 3, 3, 3, 1, 3};
	Solution                  solution;
	const vector<vector<int>> &ret = solution.groupThePeople(group);
	for (size_t               i    = 0; i < ret.size(); ++i)
	{
		for (size_t j = 0; j < ret[i].size(); ++j)
		{
			std::cout << ret[i][j] << " ";
		}
		std::cout << std::endl;
	}
}