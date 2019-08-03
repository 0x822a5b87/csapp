//
// Created by 杜航宇 on 2019-08-03.
//
//p134

#include "iostream"

using namespace std;

void rem_div(long x, long y, long *qp, long *rp)
{
    long q = x / y;
    long r = x % y;
    *qp = q;
    *rp = r;
}

// ## %bb.0:
//	pushq	%rbp
//	movq	%rsp, %rbp
//	movq	%rdi, -8(%rbp)
//	movq	%rsi, -16(%rbp)
//	movq	%rdx, -24(%rbp)
//	movq	%rcx, -32(%rbp)                 四个参数进栈
//	movq	-8(%rbp), %rax                  %rax = x
//	cqto                                    读取 %rax 的符号位，并复制到 %rdx 的所有位
//	idivq	-16(%rbp)                       %rax = %rax / y (也就是 x / y)
//	movq	%rax, -40(%rbp)                 q 进栈
//	movq	-8(%rbp), %rax                  %rax = x
//	cqto                                    读取 %rax 的符号位，并复制到 %rdx 的所有位
//	idivq	-16(%rbp)                       %rax = x / y
//	movq	%rdx, -48(%rbp)
//	movq	-40(%rbp), %rcx
//	movq	-24(%rbp), %rdx
//	movq	%rcx, (%rdx)
//	movq	-48(%rbp), %rcx
//	movq	-32(%rbp), %rdx
//	movq	%rcx, (%rdx)
//	popq	%rbp
//	retq
