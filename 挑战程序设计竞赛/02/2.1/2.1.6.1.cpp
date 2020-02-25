// 生成 {0, 1, 2, ..., n-1} 的 n! 种排列
#include "iostream"

#define MAX_N 3

int  perm[MAX_N];

static void init()
{
	for (int i = 0; i < MAX_N; ++i)
	{
		perm[i] = i;
	}
}

static void permutation(int pos)
{
	if (pos == MAX_N)
	{
		for (const int i : perm)
		{
			std::cout << i;
		}
		std::cout << std::endl;
	}

	for (int i = pos; i < MAX_N; ++i)
	{
		std::swap(perm[i], perm[pos]);
		permutation(pos + 1);
		std::swap(perm[i], perm[pos]);
	}
}


int main(int argc, char **argv)
{
	init();
	permutation(0);
}