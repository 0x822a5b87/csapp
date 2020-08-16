//
// Created by 0x822a5b87 on 2020/8/15.
//

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	vector <string> permutation(string s)
	{
		std::vector<string> v;
		permutation(v, s, 0, s.size() - 1);
		return v;
	}

	vector <string> permutation_dp(string s)
	{

	}

private:
	void permutation(vector<string> &v, string &s, size_t b, size_t e)
	{
		if (b == e)
		{
			v.push_back(s);
			return;
		}

		for (size_t i = b; i < s.size(); ++i)
		{
			std::swap(s[i], s[b]);
			permutation(v, s, b + 1, e);
			// 这里一定要把修改的字符串换回来。否则得到的结果不对
			std::swap(s[i], s[b]);
		}
	}
};

int main(int argc, char **argv)
{
	Solution solution;
	string s("abc");
	const vector<string> &v = solution.permutation(s);
	for (const auto &str : v)
	{
		std::cout << str << std::endl;
	}
}