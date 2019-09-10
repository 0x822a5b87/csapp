//
// Created by 杜航宇 on 2019-08-22.
//

#include "iostream"

long absSum(long *start, int count)
{
    long sum = 0;
    while (count > 0)
    {
        --count;
        ++start;
        sum += *start;
    }
    return sum;
}
