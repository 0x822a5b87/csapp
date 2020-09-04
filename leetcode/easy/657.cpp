//
// Created by 0x822a5b87 on 2020/8/28.
//

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	bool judgeCircle(string moves)
	{
		int x = 0, y = 0;
		for (const char ch : moves)
		{
			if (ch == 'U')
			{
				y++;
			}
			else if (ch == 'D')
			{
				y--;
			}
			else if (ch == 'L')
			{
				x++;
			}
			else if (ch == 'R')
			{
				x--;
			}
		}

		return x == 0 && y == 0;
	}
};


int main(int argc, char **argv)
{
	Solution solution;
	std::cout << solution.judgeCircle("UD") << std::endl;
}