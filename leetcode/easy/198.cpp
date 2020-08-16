//
// Created by 0x822a5b87 on 2020/8/14.
//
// dp[i] = std::max(num[i] + dp[i + 2], dp[i + 1])

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	int rob(vector<int> &nums)
	{
		if (nums.size() == 2)
		{
			return std::max(nums[0], nums[1]);
		}
		else if (nums.size() == 1)
		{
			return nums[0];
		}
		else if (nums.empty())
		{
			return -1;
		}

		vector<int> dp(nums.size());
		dp[nums.size() - 1] = nums[nums.size() - 1];
		dp[nums.size() - 2] = std::max(nums[nums.size() - 1], nums[nums.size() - 2]);
		for (int i = nums.size() - 3; i >= 0; --i)
		{
			dp[i] = std::max(nums[i] + dp[i + 2], dp[i + 1]);
		}

		std::cout << std::endl;

		return dp[0];
	}

private:
	// 递归的计算
	// 观察递归后我们可以假设 dp[i] 表示的是选择区间 [i, nums.size()) 的最大值
	int rob_rec(const vector<int> &nums, size_t b, size_t e)
	{
		if (b >= e)
		{
			return 0;
		}
		return std::max(nums[b] + rob_rec(nums, b + 2, e),
						rob_rec(nums, b + 1, e));
	}
};

int main(int argc, char **argv)
{
	Solution solution;

	std::vector<int> v{1, 2, 3, 1};
	assert(solution.rob(v) == 4);
	v = {2, 7, 9, 3, 1};
	assert(solution.rob(v) == 12);
}