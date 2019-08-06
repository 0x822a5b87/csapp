//
// Created by 杜航宇 on 2019-08-04.
//

#include "iostream"

// %rdi = x
// %eax = val
long func_a(unsigned long x)
{
    unsigned long val = 0;
    while (x) {
        // 第一次进入循环，将 val 设置为对 x 取反
        val ^= x;
        x >>= 0x1ul;
    }
    return val & 0x1ul;
}
