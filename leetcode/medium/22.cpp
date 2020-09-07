//
// Created by 0x822a5b87 on 2020/9/7.
//
// 可以使用回溯的方法代替原来的递归可以极大的优化性能

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	vector<string> generateParenthesis(int n)
	{
		std::vector<string> ret;
		if (n > 0)
		{
			string s;
			generate(ret, s, n, n);
		}
		return ret;
	}

	void generate(std::vector<string> &ret, std::string& base, int left, int right)
	{
		if (left < 0 || right < 0 || left > right)
		{
			return;
		}
		if (left == 0 && right == 0)
		{
			ret.push_back(base);
		}


		// 原来这么做的也开始实现，但是性能差很多
		// generate(ret, base+ "(", left, right - 1);
		// generate(ret, base + ")", left, right - 1);

		base.push_back('(');
		generate(ret, base, left - 1, right);
		base.pop_back();
		base.push_back(')');
		generate(ret, base, left, right - 1);
		base.pop_back();
	}
};

int main(int argc, char **argv)
{
	Solution solution;

	const vector<string> &v = solution.generateParenthesis(3);
	for (const auto &s : v)
	{
		std::cout << s << std::endl;
	}
}