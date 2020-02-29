#include "iostream"

#define N 1000

int n, m, mod;
int arr[N];

void init()
{
	std::cin >> n >> m >> mod;

	for (int i = 0; i < n; ++i)
		std::cin >> arr[i];
}

int main(int argc, char **argv)
{
	init();
}