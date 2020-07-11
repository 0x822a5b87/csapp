//
// Created by 0x822a5b87 on 2020/7/11.
//

#include "iostream"

int main(int argc, char **argv)
{
    int a[] = {1,2,3,4,5,5,6};
	std::cout << (std::lower_bound(a, a + 7, 6) - a) << std::endl;
	std::cout << (std::lower_bound(a, a + 7, 5) - a) << std::endl;
}