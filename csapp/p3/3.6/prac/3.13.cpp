//
// Created by 杜航宇 on 2019-08-03.
//

#include "iostream"

// cmpl %esi, %edi
// setl %al

int comp(int a, int b)
{
    return a < b;
}

// cmpw %si, %di
// setge %al
int comp(short a, short b)
{
    return a >= b;
}

// cmpq %rsi, %rdi
// setne %a

// cmpq 代表是四字节
// setne 可以表示有符号，无符号和指针参数
