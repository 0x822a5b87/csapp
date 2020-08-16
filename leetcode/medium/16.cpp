//
// Created by 0x822a5b87 on 2020/8/14.
//

#include "iostream"
#include "vector"

class Solution
{
public:
	std::vector<int> swapNumbers(std::vector<int> &numbers)
	{
		numbers[0] ^= numbers[1];
		numbers[1] ^= numbers[0];
		numbers[0] ^= numbers[1];
		return numbers;
	}
};

int main(int argc, char **argv)
{
	std::vector<int> numbers{1, 2};
	Solution solution;
	solution.swapNumbers(numbers);

	assert(numbers[0] == 2);
	assert(numbers[1] == 1);
}