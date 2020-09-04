//
// Created by 0x822a5b87 on 2020/8/19.
//
// 计算回文数字有两个思路：
// 1. 枚举所有可能的生成字符，并且检查每一个字符是否为回文字符
// 2. 找到一个回文字符，并且使用一个指针向两边拓展，直到找到所有的回文字符。
//    根据题意的描述，每一个单独的字符都是一个回文字。所以我们可以找到遍历整个字符串得到所有的单个字符子串。
//    然后通过这个字符子串向两边拓展。
//	  回文字的查找有两种：
// 2.1 回文字是奇数个，所以以 s[i] 作为原点向两边搜索。
// 2.2 回文字是偶数个，所以以 s[i],s[i+1] 作为原点向两边搜索，并且 s[i] == s[i+1]

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	int countSubstrings(const string &s)
	{
		return countSubstringsDp(s);
	}

	int countSubstringsRec(const string &s)
	{
		int count = 0;
		for (size_t i = 0; i < s.size(); ++i)
		{
			count += countSub(s, i, i);
			count += countSub(s, i, i + 1);
		}
		return count;
	}

	int countSubstringsDp(const string &s)
	{
		return 0;
	}

private:
	int countSub(const string &s, int b, size_t e)
	{
		int count = 0;
		while (b >= 0 && e < s.size() && s[b--] == s[e++])
		{
			++count;
		}
		return count;
	}
};

int main(int argc, char **argv)
{
	Solution solution;
	std::cout << solution.countSubstringsRec("abccba") << std::endl;
	assert(9 == solution.countSubstringsRec("abccba"));
	assert(3 == solution.countSubstringsRec("abc"));
	assert(6 == solution.countSubstringsRec("aaa"));
	return 0;
}