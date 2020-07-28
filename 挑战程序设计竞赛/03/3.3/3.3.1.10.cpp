#include <vector>
#include "iostream"

int main(int argc, char **argv)
{
	std::vector<int> v {1,2,3,3,3,3,4,5};
	std::cout << std::upper_bound(v.begin(), v.end(), 3) - v.begin() << std::endl;
}