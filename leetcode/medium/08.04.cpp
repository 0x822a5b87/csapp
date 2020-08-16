
//
// Created by 0x822a5b87 on 2020/8/15.
//

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	vector<vector<int>> subsets2(vector<int> &nums)
	{
		vector<vector<int>> v;
		for (size_t i = 0; i < (1u << (nums.size())); ++i)
		{
			vector<int> s;
			for (size_t j = 1, cnt = 0; j <= i; j = j << 1u, ++cnt)
			{
				if ((j & i) != 0u)
				{
					s.emplace_back(nums[cnt]);
				}
			}
			v.emplace_back(s);
		}
		return v;
	}

	vector<vector<int>> subsets(vector<int> &nums)
	{
		vector<vector<int>> v;
		v.emplace_back();
		for (size_t i = 0; i < nums.size(); ++i)
		{
			size_t sz = v.size();
			for (size_t j = 0; j < sz; ++j)
			{
				vector<int> s(v[j]);
				s.push_back(nums[i]);
				v.push_back(s);
			}
		}
		return v;
	}
};

int main(int argc, char **argv)
{
	Solution solution;
	vector<int> v{1, 2, 3};
	const vector<vector<int>> &ret = solution.subsets(v);
	for (int i = 0; i < ret.size(); ++i)
	{
		for (int j = 0; j < ret[i].size(); ++j)
		{
			std::cout << ret[i][j] << " ";
		}
		std::cout << std::endl;
	}
}