//
// Created by 0x822a5b87 on 2020/8/27.
//
// 假设我们使用一个栈来辅助计算的话，那么栈的深度就是括号的 depth
// 只要在遍历过程中，我们保证栈内一半的括号属于序列 A，一半的括号属于序列 B
// 那么就能保证拆分后最大的嵌套深度最小，是当前最大嵌套深度的一半。
// 在这里我们需要注意的一点是，为什么这样可以保证深度是最小深度
// 因为我们的原始数组的深度可能是 ABC 这种类型，而最大深度取决于 A，B，C 中深度最大的那个
// 也就是说，我们使用这个策略可以将 A，B，C 中任意一个合法括号对的深度减半
// 此外，由于在这个问题中，栈中只会存放 (，因此我们不需要维护一个真正的栈，只需要用一个变量模拟记录栈的大小。

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	vector<int> maxDepthAfterSplit(string seq)
	{
		size_t d = 0;
		vector<int> ret;
		for (const char ch : seq)
		{
			if (ch == '(')
			{
				++d;
				ret.push_back(d % 2);
			}
			else if (ch == ')')
			{
				ret.push_back(d % 2);
				--d;
			}
		}
		return ret;
	}
};
