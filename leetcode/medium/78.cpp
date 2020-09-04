//
// Created by 0x822a5b87 on 2020/8/27.
//
// 有两个需要注意的店
// 1. 我们不能使用迭代器在遍历容器的同时去编辑它，但是可以通过下标访问来实现
// 2. 在内部的循环中，必须在最开始确定 sz 的值

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	vector<vector<int>> subsets(vector<int> &nums)
	{
		vector<vector<int>> ret{{}};
		for (const int n : nums)
		{
			size_t sz = ret.size();
			for (size_t i = 0; i < sz; ++i)
			{
				vector<int> tmp{ret[i]};
				tmp.push_back(n);
				ret.push_back(tmp);
			}
		}
		return ret;
	}
};

int main(int argc, char **argv)
{
	Solution solution;
	vector<int> nums{1,2,3};
	const vector<vector<int>> &v = solution.subsets(nums);
	std::cout << v.size() << std::endl;
}