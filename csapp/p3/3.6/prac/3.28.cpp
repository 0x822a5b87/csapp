//
// Created by 杜航宇 on 2019-08-04.
//

#include "iostream"

// %rdi = x
// %rax = %eax = val
// %rcx = %ecx =
// %rdx = %edx = i
unsigned long fun_b(unsigned long x)
{
    unsigned long val = 0;
    long i;
    for (i = 64; i > 0; --i)
    {
        // x & 0x1u     保留 x 的最低位
        // val << 1u    移动 val 的最高位到最低位
        // 如果 x 的最低位为 1，那么将 val 的最高位设置为 0
        // 如果 x 的最地位为 0，那么保留 val 的最高位
        // 由于 val 初始化为 0，那么 val 的最高位在没有修改过的情况下肯定为 0.而在我们的循环中每次只会修改一位
        // 所以可以认为本行代码的作用是将 val 的最低位设置为 x 的最低位

        // 我们总共会执行 64 次循环，也就是说会设置 val 的每一位
        // 在第一次循环中，将 val 的最高位设置为 x 的最低位
        // 在第二次循环中，将 val 的高二位设置为 x 的第二位
        val = (val << 1u) | (x & 0x1u);
        x >>= 1u;
    }
    return val;
}

int main()
{
    unsigned long x = 0xFFFFFFFF00000000;
    std::cout << std::hex << fun_b(x) << std::endl;
}
