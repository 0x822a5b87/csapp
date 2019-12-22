//
// Created by 杜航宇 on 2019-08-07.
//

#include "iostream"

long swap_and(long *xp, long *yp)
{
    long x = *xp;
    long y = *yp;
    *xp = y;
    *yp = x;

    return x + y;
}

long caller()
{
    long arg1 = 534;
    long arg2 = 1057;
    long sum = swap_and(&arg1, &arg2);
    long diff = arg1 - arg2;
    asm(
            "subq   $32, %rsp"
            );

    return sum * diff;
}

