//
// Created by 0x822a5b87 on 2020/8/14.
//

#include "iostream"
#include "cmath"

class Solution
{
public:
	int sumNums(int n)
	{
		double v = std::pow(n, 2) + n;

		return static_cast<int>(v) >> 1;
	}
};

int main(int argc, char **argv)
{
	Solution solution;

	assert(solution.sumNums(1) == 1);
	assert(solution.sumNums(2) == 3);
	assert(solution.sumNums(10) == 55);
}