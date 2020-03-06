#include "iostream"

#define INF   0xffff
#define MAX_V 1024
#define MAX_E 1024

int V, E;

int D[MAX_V];
bool used[MAX_V];

void init()
{
	std::cin >> V >> E;
	std::fill(D, D + V, INF);
}