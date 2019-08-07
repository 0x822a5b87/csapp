//
// Created by 杜航宇 on 2019-08-06.
//

#include "iostream"

void test_init()
{
    int x[INT_MAX];
    x[INT_MAX - 100] = -1;

    int i = 0;
    for (; x[i] != -1; ++i)
    {
    }
    std::cout << x[i-1] << std::endl;
}

int main()
{
    test_init();
}
