//
// Created by 杜航宇 on 2019-09-05.
//

#include "iostream"

void merge(const long src1[], const long src2[], long dest[], long n)
{
    long i1 = 0, i2 = 0, id = 0;
    while (i1 < n && i2 < n)
    {
        long v1 = src1[i1];
        long v2 = src2[i2];
        bool take = v1 < v2;
        dest[id++] = take ? v1 : v2;
        i1 += take;
        i2 += (1 - take);
    }

    while (i1 < n)
    {
        dest[id++] = src1[i1++];
    }

    while(i2 < n)
    {
        dest[id++] = src2[i2++];
    }
}
