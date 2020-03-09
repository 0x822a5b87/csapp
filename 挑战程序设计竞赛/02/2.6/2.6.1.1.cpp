#include "iostream"

int gcd(int a, int b)
{
	if (a < b)
	{
		std::swap(a, b);
	}
	if (b == 0)
	{
		return a;
	}

	return gcd(b, a % b);
}

int main(int argc, char **argv)
{
	int x1, y1, x2, y2;
	std::cin >> x1 >> y1 >> x2 >> y2;

	int a = (x1 > x2) ? (x1 - x2) : (x2 - x1);
	int b = (y1 > y2) ? (y1 - y2) : (y2 - y1);

	std::cout << (gcd(a, b) - 1) << std::endl;
}
