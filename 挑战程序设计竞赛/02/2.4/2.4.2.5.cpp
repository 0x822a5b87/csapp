#include "iostream"

// 并查集的实现

#define N 100

int par[N];
int rank[N];

static int find(int x);

void init()
{
	for (int i = 0; i < N; ++i)
	{
		par[i]  = i;
		rank[i] = 0;
	}
}

bool same(int m, int n)
{
	return find(m) == find(n);
}

void unite(int m, int n)
{
	m = find(m);
	n = find(n);
	if (m == n)
	{
		return;
	}
	if (rank[m] > rank[n])
	{
		par[n] = par[m];
	}
	else
	{
		par[m] = par[n];
		if (rank[m] == rank[n])
		{
			rank[m]++;
		}
	}
}

static int find(int x)
{
	if (par[x] == x)
	{
		return x;
	}
	return find(par[x]);
}

//int main(int argc, char **argv)
//{
//	init();
//	for (int i = 0; i < N - 1; ++i)
//	{
//		assert(!same(i, i + 1));
//	}
//
//	for (int i = 0; i < N; ++i)
//	{
//		if (i % 2 == 0)
//		{
//			unite(i, i + 1);
//		}
//		else
//		{
//			assert(same(i, i - 1));
//		}
//	}
//}