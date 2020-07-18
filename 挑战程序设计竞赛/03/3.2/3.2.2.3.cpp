#include "iostream"

int main(int argc, char **argv)
{
	unsigned s = 109;
	// 0110 1101
	unsigned sub = s;
	std::cout << s << std::endl;
	do
	{
		sub = (sub - 1) & s;
		std::cout << std::bitset<8>(sub) << " " << sub << std::endl;
	} while (sub != s);
}
