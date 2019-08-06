//
// Created by 杜航宇 on 2019-08-03.
//

#include "iostream"

void test_if(int x)
{
    if (x)
    {
        printf("x = %d", x);
    }
    else
    {
        printf("x = 0");
    }
}

// ## %bb.0:
//	pushq	%rbp
//	movq	%rsp, %rbp
//	subq	$16, %rsp
//	movl	%edi, -4(%rbp)
//	cmpl	$0, -4(%rbp)           if (x == 0)
//	je	LBB0_2                     为真则跳转到 LBB0_2，否则继续执行后续代码
//## %bb.1:
//	movl	-4(%rbp), %esi
//	leaq	L_.str(%rip), %rdi
//	movb	$0, %al
//	callq	_printf
//	movl	%eax, -8(%rbp)          ## 4-byte Spill
//	jmp	LBB0_3
//LBB0_2:
//	leaq	L_.str.1(%rip), %rdi
//	movb	$0, %al
//	callq	_printf
//	movl	%eax, -12(%rbp)         ## 4-byte Spill
//LBB0_3:
//	addq	$16, %rsp
//	popq	%rbp
//	retq
//                                        ## -- End function
// L_.str:                                 ## @.str
//	.asciz	"x = %d"
//
//L_.str.1:                               ## @.str.1
//	.asciz	"x = 0"
