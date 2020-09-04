//
// Created by 0x822a5b87 on 2020/8/27.
//

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	vector<vector<int>> permute(vector<int> &nums)
	{
		vector<vector<int>> ret;
		permute(ret, nums, 0, nums.size());
		return ret;
	}

private:
	void permute(vector<vector<int>> &ret, vector<int> &nums, size_t lb, size_t ub)
	{
		if (lb == ub)
		{
			ret.push_back(nums);
		}
		for (size_t i = lb; i < ub; ++i)
		{
			std::swap(nums[lb], nums[i]);
			permute(ret, nums, lb + 1, ub);
			std::swap(nums[lb], nums[i]);
		}
	}
};

int main(int argc, char **argv)
{
	Solution    solution;
	vector<int> v{1, 2, 3};
	solution.permute(v);
}