// 有 1，5，10，50，100，500 六种面额的硬币
// 各 c1, c5, c10, c50, c100, c500 张
// 需要支付 A 元，最少需要多少枚硬币。

// 这题有一个贪心算法：因为任何一个较大的数字都可以被分解为较小的数字的和
// 也就是说：有大面额的尽量用大面额的，因为需要的硬币数较少
// 并且不存在，使用了大面额之后用小面额无法找零成功的情况。
// 如果不满足我们前面提到的条件则无法使用贪心算法。
#include "iostream"

const char *format = "C1 = %d, C5 = %d, C10 = %d, C50 = %d, C100 = %d, C500 = %d, A = %d";
const int coins[6] = {1, 5, 10, 50, 100, 500};

int C[6];

int A;

void solve()
{
	std::string line;
	std::getline(std::cin, line);
	int c1,c5,c10,c50,c100,c500,sum;
	sscanf(line.c_str(), format, &c1, &c5, &c10, &c50, &c100, &c500, &sum);
	C[0] = c1;
	C[1] = c5;
	C[2] = c10;
	C[3] = c50;
	C[4] = c100;
	C[5] = c500;
	int cnt = 0;
	for (int i = 5; i >= 0; --i)
	{
		while (sum != 0 && C[i] > 0 && sum >= coins[i])
		{
			sum -= coins[i];
			C[i]--;
			++cnt;
		}
	}
	std::cout << cnt << std::endl;
}


void solve2()
{
	int ans = 0;
	for (int i = 5; i >= 0; i--)
	{
		int t = std::min(A / coins[i], C[i]);
		A -= t * coins[i];
		ans += t;
	}
}

int main(int argc, char **argv)
{
	solve();
}