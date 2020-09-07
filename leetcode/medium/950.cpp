//
// Created by 0x822a5b87 on 2020/9/7.
//
// 将整个过程反向执行即可
// a = [2,13,3,11,5,17,7]
// b = [2,3,5,7,11,13,17]
//
// 1.从a头部拿一个数出来，从尾部添加到b中；
// 2.从a头部拿一个数，添加到a的末尾。
// 先在逆转过来，由于最开始 a 肯定为空，所以我们先操作 b
// 1. 从 b 的尾部取出一个数字，加到 a 的头部
// 2. 从 a 的末尾取出一个数字，加到 a 的头部

#include "iostream"
#include "vector"
#include "deque"

using namespace std;

class Solution
{
public:
	vector<int> deckRevealedIncreasing(vector<int> &deck)
	{
		deque<int> tmp;
		std::sort(std::begin(deck), std::end(deck));
		// 最开始 tmp 为空，我们需要初始化一下它
		tmp.push_front(deck.back());
		for (int i = deck.size() - 2; i >= 0; --i)
		{
			tmp.push_front(tmp.back());
			tmp.pop_back();
			tmp.push_front(deck[i]);
		}

		return std::vector<int>(std::begin(tmp), std::end(tmp));
	}
};

int main(int argc, char **argv)
{
	Solution         solution;
	// 2 13 3 11 5 17 7
	// 7 2 13 3 11 5 17
	std::vector<int> ret{1, 2, 3};
	ret = solution.deckRevealedIncreasing(ret);

	for (const auto &num : ret)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;

	ret = solution.revDeckRevealedIncreasing(ret);
	for (const auto &num : ret)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
}