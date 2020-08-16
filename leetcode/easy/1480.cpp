//
// Created by 0x822a5b87 on 2020/8/14.
//

#include "iostream"
#include "vector"

class Solution
{
public:
	std::vector<int> runningSum(std::vector<int> &nums)
	{
		std::vector<int> ret;
		if (nums.empty())
		{
			return ret;
		}
		ret.resize(nums.size());
		ret[0] = nums[0];
		for (std::size_t i = 1; i < nums.size(); ++i)
		{
			ret[i] = nums[i] + ret[i - 1];
		}
		return ret;
	}
};

int main(int argc, char **argv)
{
	Solution solution;

	std::vector<int> v{};
	v = solution.runningSum(v);
	assert(v.empty());

	v = {1};
	v = solution.runningSum(v);
	assert(v[0] == 1);

	v = {1, 2 ,3};
	v = solution.runningSum(v);
	assert(v[0] == 1);
	assert(v[1] == 3);
	assert(v[2] == 6);
}