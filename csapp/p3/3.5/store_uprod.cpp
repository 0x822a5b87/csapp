//
// Created by 杜航宇 on 2019-08-03.
//

// p134
#include "stdint.h"

typedef unsigned __int128 uint128_t;

void store_uprod(uint128_t *dest, uint64_t x, uint64_t y)
{
    *dest = x * (uint128_t) y;
}
// rbp 被调用者保存
// rsp 栈指针

// unsigned 的乘法可以直接用 movq 来实现
// ## %bb.0:
//    pushq   %rbp
//    movq    %rsp, %rbp                        保存栈指针
//    movq    %rdi, -8(%rbp)
//    movq    %rsi, -16(%rbp)
//    movq    %rdx, -24(%rbp)                   三个参数入栈
//    movq    -16(%rbp), %rax                   %rax = x
//    movq    -24(%rbp), %rdx                   %rdx = y
//    mulq    %rdx                              将 y 转换为 uint128_t
//    movq    -8(%rbp), %rsi                    %rsi = dest
//    movq    %rdx, 8(%rsi)                     将高 8 字节设置为 y
//    movq    %rax, (%rsi)                      将低 8 字节设置为 x，针对小端法及其，高位字节存储在大地址
//    popq    %rbp
//    retq

void store_uprod_signed(long *dest, int x, int y)
{
    *dest = x * y;
}

// ## %bb.0:
//	pushq	%rbp
//	movq	%rsp, %rbp
//	movq	%rdi, -8(%rbp)
//	movl	%esi, -12(%rbp)
//	movl	%edx, -16(%rbp)                     三个参数入栈
//	movl	-12(%rbp), %edx                     %edx = x
//	imull	-16(%rbp), %edx                     %edx = x * y
//	movslq	%edx, %rdi                          4 字转换为 8 字，高位补符号位
//	movq	-8(%rbp), %rax                      %rax = dest
//	movq	%rdi, (%rax)                        *dest = x * y  (x * y 是转换为 8 字后的)
//	popq	%rbp
//	retq
