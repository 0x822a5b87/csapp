//
// Created by 杜航宇 on 2019-08-13.
//

#include "iostream"

int func(const int x, const int y)
{
    return x + y;
}

int main()
{
    int (*fp1)(int, int) = func;
    using fp2 = int (*)(int, int);
    fp2 fp = func;
}
