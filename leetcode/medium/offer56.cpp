//
// Created by 0x822a5b87 on 2020/8/19.
//
// 算法的思路很简单：对于一整个数组，如果我们使用一个数组来统计每一位中 1 出现的次数，那么最后我们就知道哪一位
// 出现了四次，而其他位则出现了三次。将 1 出现 4 次的位置为 1，出现 3 次的位置为 0。那么计算就得到了我们的数字
// 要表示 3，我们需要用两个数字才能够表示。因为每一位需要用两位来表示
// 接下来，需要通过 状态转换表 导出 状态转换的计算公式 。首先回忆一下位运算特点，对于任意二进制位 xx ，有：
// x ^ 0 = x
// x ^ 1 = ~x
// x & 0 = 0
// x & 1 = 1
//
// 假设现在数字某一位的状态为 two one，那么就可以得到我们的状态机了。
// 接受到 1 时就修改状态
// 0 -> 1 -> 2 -> 0
//
// if two == 0:
//  if n == 0:
//    one = one
//  if n == 1:
//    one = ~one
// if two == 1:
//    one = 0
//
// 简化一下得到
// if two == 0:
//		one ^= n
// if two == 1:
//		one = 0
//
// 再简化一下得到
// one = one ^ n & ~two
//
// 下面我们需要计算 two
// 那么 two 的计算也是一样的，但是有一点需要注意的是，我们是先计算的 one
// if one == 0:
//		if n == 0:
//			two = two
//		if n == 1:
//			two = 1
// if one == 1:
//		two = ~two				# 注意，在这里我开始计算错了 two = 0，实际上状态的变化是有 0 -> 1 和  1 -> 0 两个状态的
//
// 简化一下得到
// if one == 0:
//		two = two | n
// if one == 1:
//		two = 0
//
// 继续简化得到
// two = two | n & ~one

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	int singleNumber(vector<int> &nums)
	{
		int            one = 0, two = 0;
		for (const int n : nums)
		{
			one = one ^ n & ~two;
			two = two ^ n & ~one;
		}
		return one;
	}
};

int main(int argc, char **argv)
{
	Solution    solution;
	vector<int> v{1, 1, 1, 2, 2, 2, 3, 4, 4, 4};
	std::cout << solution.singleNumber(v) << std::endl;
}