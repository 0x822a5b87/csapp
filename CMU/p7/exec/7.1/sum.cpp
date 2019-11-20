//
// Created by 杜航宇 on 2019-10-23.
//

#include "iostream"

int sum(int *a, int n)
{
    int i, s = 0;
    for (i = 0; i < n; ++i)
    {
        s += a[i];
    }
    return s;
}
