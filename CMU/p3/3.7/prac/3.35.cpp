//
// Created by 杜航宇 on 2019-08-07.
//

#include "iostream"

long rfun(unsigned long x)
{
    if (x == 0)
    {
        return 0;
    }
    unsigned long nx = x >> 2u;
    long rv = rfun(nx);
    // 注意这里
    // addq %rbx, %rax
    // %rax 是 rfun() 的返回值很简单
    // %rbx 可以看到是一个被调用者保存寄存器，所以在 call rfun 前后保持一致
    // 而在我们的函数中，我们通过 movq %rdi, %rbx 赋予 %rbx 为 x
    return x + nx;
}
