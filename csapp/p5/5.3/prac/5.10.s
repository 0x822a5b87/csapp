	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z6clear0Pll           ## -- Begin function _Z6clear0Pll
	.p2align	4, 0x90
__Z6clear0Pll:                          ## @_Z6clear0Pll
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, -20(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movslq	-20(%rbp), %rax
	cmpq	-16(%rbp), %rax
	je	LBB0_4
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-8(%rbp), %rax
	movslq	-20(%rbp), %rcx
	movq	$0, (%rax,%rcx,8)
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB0_1
LBB0_4:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z6clear1Pll           ## -- Begin function _Z6clear1Pll
	.p2align	4, 0x90
__Z6clear1Pll:                          ## @_Z6clear1Pll
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rsi
	movq	-16(%rbp), %rdi
	shlq	$3, %rdi
	addq	%rdi, %rsi
	movq	%rsi, -24(%rbp)
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	-8(%rbp), %rax
	cmpq	-24(%rbp), %rax
	je	LBB1_3
## %bb.2:                               ##   in Loop: Header=BB1_1 Depth=1
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	addq	$8, %rcx
	movq	%rcx, -8(%rbp)
	movq	$0, (%rax)
	jmp	LBB1_1
LBB1_3:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
