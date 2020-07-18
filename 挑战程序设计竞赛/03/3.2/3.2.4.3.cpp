#include <vector>
#include "iostream"

int main(int argc, char **argv)
{
	int num = 100;
	std::vector<int> v{1,2,3,5,6,8};
	auto it = std::lower_bound(v.begin(), v.end(),0);
	std::cout << *it << std::endl;
	std::cout << *(it - 1) << std::endl;
}