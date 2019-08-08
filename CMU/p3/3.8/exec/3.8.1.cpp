//
// Created by 杜航宇 on 2019-08-08.
//

#include "iostream"

int main()
{
    long e[10];
    std::cout << &e[1] << std::endl;
    std::cout << e << std::endl;
    std::cout << &e[1] - e << std::endl;
}
