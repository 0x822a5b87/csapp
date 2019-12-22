//
// Created by 杜航宇 on 2019-08-03.
//
#include "iostream"

long test(long x, long y, long z)
{
    long val = x + y + z;
    // cmpq $-3, %rdi
    // jge .L2
    // 如果 %rdi >= -3 则跳转到 .L2，所以很容易得知这里 if 的判断条件
    if (x < -3)
    {
        // cmpq %rdx, %rsi
        // jge .L3
        // if (%rsi >= %rdx)
        //      goto .L3
        if (y < z)
        {
            val = x * y;
        }
        else
        {
            // .L3
            val = y * z;
        }
    }
    // .L2
    else if (x > 2)
    {
        val = x * y;
    }

    // .L4
    return val;
}
