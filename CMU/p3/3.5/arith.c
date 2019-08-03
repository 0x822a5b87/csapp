//
// Created by 杜航宇 on 2019-08-03.
//

long arith(long x, long y, long z)
{
    long t1 = x ^ y;
    long t2 = z * 48;
    long t3 = t1 & 0x0F0F0F0F;
    long t4 = t2 - t3;

    return t4;
}

// rdi 第一个参数
// rsi 第二个参数
// rdx 第三个参数

//_arith:                                 ## @arith
//## %bb.0:
//pushq	%rbp
//movq	%rsp, %rbp
//movq	%rdi, -8(%rbp)                      将第一个参数压入栈
//movq	%rsi, -16(%rbp)                     将第二个参数压入栈
//movq	%rdx, -24(%rbp)                     将第三个参数压入栈
//movq	-8(%rbp), %rdx                      读取 x 到 %rdx
//xorq	-16(%rbp), %rdx                     %rdx = x ^ y
//movq	%rdx, -32(%rbp)                     将 x ^ y(t1) 压入栈
//imulq	$48, -24(%rbp), %rdx                %rdx = 48 * z
//movq	%rdx, -40(%rbp)                     将 48 * z(t2) 压入栈
//movq	-32(%rbp), %rdx                     %rdx = t1
//andq	$252645135, %rdx                    %rdx = t1 & 0x0F0F0F0F
//movq	%rdx, -48(%rbp)                     将 t3 压入栈
//movq	-40(%rbp), %rdx                     %rdx = t2
//subq	-48(%rbp), %rdx                     %rdx = t2 - t3
//movq	%rdx, -56(%rbp)                     将 t4 = t2 - t3 压入栈
//movq	-56(%rbp), %rax                     %rax = t4
//popq	%rbp
//retq

