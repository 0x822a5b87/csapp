// 最长公共子序列（不要求连续）

#include "iostream"

int len1, len2;
std::string word1, word2;

void init()
{
	std::cin >> len1 >> len2
			 >> word1 >> word2;
}

void solve()
{
	int dp[len1 + 1][len2 + 1];
	for (size_t i = 0; i <= len2; ++i)
	{
		dp[0][i] = 0;
	}

	for (size_t j = 0; j <= len1; ++j)
	{
		dp[j][0] = 0;
	}

	for (size_t i = 1; i <= len1; ++i)
	{
		for (size_t j = 1; j <= len2; ++j)
		{
			if (word1[i] == word2[j])
			{
				dp[i][j] = dp[i-1][j-1] + 1;
			}
			else
			{
				dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
			}
		}
	}

	std::cout << dp[len1][len2] << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}
