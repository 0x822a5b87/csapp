//
// Created by 杜航宇 on 2019-08-05.
//

#include "iostream"

void switcher(long a, long b, long c, long *dest)
{
    long val;
    switch (a)
    {
        case 5:
            // .L7
            c = b ^ 15;
        case 0:
            val = c + 112;
            // .L3
            break;
        case 2:
        case 7:
            // .L5
            val = b + c;
            val <<= 2;
            break;
        case 4:
            // .L6
            val = a;
            break;
        default:
            // .L2
            val = b;
            break;
    }
    *dest = val;
}
