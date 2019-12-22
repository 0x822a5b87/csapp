//
// Created by 杜航宇 on 2019-08-07.
//

#include "iostream"

void proc(long a1, long *a1p,
          int a2, int *a2p,
          short a3, short *a3p,
          char a4, char *a4p)
{
    *a1p += a1;
    *a2p += a2;
    *a3p += a3;
    *a4p += a4;
}

// % rsp 是堆栈指针寄存器，通常会指向栈顶位置，堆栈的 pop 和 push 操作就是通过改变 % rsp 的值即移动堆栈指针的位置来实现的。
// % rbp 是栈帧指针，用于标识当前栈帧的起始位置

// 在我们这个例子中，8(%rbp) 记录的是调用该函数的返回地址。当本函数执行完成之后需要通过这个返回地址来上级函数的位置
// 	# 初始化 8 个参数
//	movq	24(%rbp), %r10
//	movb	16(%rbp), %r11b
//	movq	%rdi, -16(%rbp)
//	movq	%rsi, -24(%rbp)
//	movl	%edx, -28(%rbp)
//	movq	%rcx, -40(%rbp)
//	movw	%ax, -42(%rbp)
//	movq	%r9, -56(%rbp)
//
//  # *a1p += a1;
//	movq	-16(%rbp), %rcx                 # tmp1 = a1
//	movq	-24(%rbp), %rsi                 # tmp2 = a1p
//	addq	(%rsi), %rcx                    # tmp1 += *tmp2
//	movq	%rcx, (%rsi)                    # *a1p = tmp1

