//
// Created by 0x822a5b87 on 2020/8/15.
//

// https://leetcode-cn.com/problems/generate-parentheses/solution/hui-su-suan-fa-by-liweiwei1419/

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	vector <string> generateParenthesis(int n)
	{
		vector<string> res;
		dfs(res, n, n, "");
		return res;
	}

	void dfs(vector<string> &res, int left, int right, string cur)
	{
		if (left == 0 && right == 0)
		{
			res.push_back(cur);
			return;
		}

		if (right < left)
		{
			return;
		}

		if (left > 0)
		{
			dfs(res, left - 1, right, cur + '(');
		}

		if (right > 0)
		{
			dfs(res, left, right - 1, cur + ')');
		}
	}
};

int main(int argc, char **argv)
{
	Solution solution;
	auto v = solution.generateParenthesis(3);
	for (const string &s : v)
	{
		std::cout << s << std::endl;
	}
}