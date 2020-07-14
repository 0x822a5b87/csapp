#include "iostream"
#include "vector"

const int max_len = 15;

const int WHITE = 0;
const int BLACK = 1;

const int IS_FLIP = 1;

unsigned m, n;

std::vector<std::vector<int>> ret;
std::vector<std::vector<int>> BOARD;

void init()
{
	std::cin >> m >> n;
	// vector 的初始容量为空，必须通过 resize 或者 reserve 调整容量
	BOARD.resize(m);
	ret.resize(m);
	for (int i = 0; i < m; ++i)
	{
		BOARD[i].resize(n);
		ret[i].resize(n);
		for (int j = 0; j < n; ++j)
		{
			std::cin >> BOARD[i][j];
			std::cout << BOARD[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void flip_value(std::vector<std::vector<int>> &board, int i, int j)
{
	if (i >= 0 && i < m && j >= 0 && j < n)
	{
		board[i][j] = (board[i][j] == BLACK ? WHITE : BLACK);
	}
}

void do_flip(std::vector<std::vector<int>> &board, int i, int j)
{
	flip_value(board, i, j);
	flip_value(board, i - 1, j);
	flip_value(board, i + 1, j);
	flip_value(board, i, j - 1);
	flip_value(board, i, j + 1);
}

void judge(std::vector<std::vector<int> > board)
{
	for (int i = 0; i < n; ++i)
	{
		if (ret[0][i])
		{
			do_flip(board, 0, i);
		}
	}

	// 当到这一行时，第一行的翻转情况已经确定了
	for (int i = 1; i < m - 1; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int  color = board[i - 1][j];
			if (color == BLACK)
			{
				do_flip(board, i, j);
				ret[i][j] = true;
			}
			else
			{
				ret[i][j] = false;
			}
		}
	}

	// 检查最后一行是否为全白，不是的话说明对于固定的第一行，无解
	for (int i = 0; i < n; ++i)
	{
		if (board[m - 1][i] == BLACK)
		{
			return;
		}
	}

	std::cout << "========================" << std::endl;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cout << ret[i][j] << " ";
		}

		std::cout << std::endl;
	}
	std::cout << "========================" << std::endl;
}

void solve(std::vector<std::vector<int>> &board)
{
	// 注意这里的循环，我们可以把第一行当做是一个二进制的数字，每个数字表示当前这一位是0或者是1
	for (unsigned i = 0; i < (1u << n); ++i)
	{
		for (unsigned j = 0; j < n; ++j)
		{
			ret[0][n - j - 1] = ((i >> j) & 1u);
		}
		judge(board);
	}
}

int main(int argc, char **argv)
{
	init();

	std::vector<std::vector<int>> board(BOARD);

	solve(board);

	return 0;
}