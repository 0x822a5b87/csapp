#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

const int N = 20010, INF = 0x3f3f3f3f;
int n, m, r;
struct edge
{
	int st, en, cost;
} g[N*10];
int par[N];
bool cmp(edge a, edge b)
{
	return a.cost < b.cost;
}
void init(int n)
{
	for(int i = 0; i <= n; i++) par[i] = i;
}
int _find(int x)
{
	int r = x, i = x, j;
	while(r != par[r]) r = par[r];
	while(i != r) j = par[i], par[i] = r, i = j;
	return r;
}
void unite(int x, int y)
{
	x = _find(x), y = _find(y);
	if(x == y) return;
	par[x] = y;
}
int kruskal()
{
	sort(g + 1, g + 1 + r, cmp);
	init(n + m);
	int sum = 0;
	for(int i = 1; i <= r; i++)
		if(_find(g[i].st) != _find(g[i].en))
			sum += g[i].cost, unite(g[i].st, g[i].en);
	return sum;
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &m, &r);
		for(int i = 1; i <= r; i++)
		{
			scanf("%d%d%d", &g[i].st, &g[i].en, &g[i].cost);
			g[i].en += n, g[i].cost = -g[i].cost;
		}
		printf("%d\n", (n + m) * 10000 + kruskal());
	}
	return 0;
}
