/**
 * 输入：rating = [2,5,3,4,1]
 * 输出：3
 * 解释：我们可以组建三个作战单位 (2,3,4)、(5,4,1)、(5,3,1) 。
 */

#include "iostream"
#include "vector"

class Solution
{
public:
	int numTeams(std::vector<int> &rating)
	{
		if (rating.empty())
		{
			return 0;
		}

		int         total = 0;
		for (size_t j     = 0; j < rating.size(); ++j)
		{
			int         left_b = 0, left_s = 0, right_b = 0, right_s = 0;
			for (size_t i      = 0; i < j; ++i)
			{
				if (rating[i] < rating[j])
				{
					++left_s;
				}
				else if (rating[j] < rating[i])
				{
					++left_b;
				}
			}

			for (size_t k = j + 1; k < rating.size(); ++k)
			{
				if (rating[j] < rating[k])
				{
					++right_b;
				}
				else if (rating[k] < rating[j])
				{
					++right_s;
				}
			}

			total += left_b * right_s + left_s * right_b;
		}
		return total;
	}
};

int main(int argc, char **argv)
{
	Solution         solution;
	std::vector<int> v{2, 5, 3, 4, 1};
	assert(solution.numTeams(v) == 3);
	v = {2, 1, 3};
	assert(solution.numTeams(v) == 0);
	v = {1, 2, 3, 4};
	assert(solution.numTeams(v) == 4);
}