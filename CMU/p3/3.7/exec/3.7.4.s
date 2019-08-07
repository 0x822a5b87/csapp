	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z8swap_andPlS_        ## -- Begin function _Z8swap_andPlS_
	.p2align	4, 0x90
__Z8swap_andPlS_:                       ## @_Z8swap_andPlS_
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
	movq	(%rsi), %rsi
	movq	%rsi, -24(%rbp)
	movq	-16(%rbp), %rsi
	movq	(%rsi), %rsi
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rsi
	movq	-8(%rbp), %rdi
	movq	%rsi, (%rdi)
	movq	-24(%rbp), %rsi
	movq	-16(%rbp), %rdi
	movq	%rsi, (%rdi)
	movq	-24(%rbp), %rsi
	addq	-32(%rbp), %rsi
	movq	%rsi, %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z6callerv             ## -- Begin function _Z6callerv
	.p2align	4, 0x90
__Z6callerv:                            ## @_Z6callerv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	$534, -8(%rbp)          ## imm = 0x216
	movq	$1057, -16(%rbp)        ## imm = 0x421
	leaq	-8(%rbp), %rdi
	leaq	-16(%rbp), %rsi
	callq	__Z8swap_andPlS_
	movq	%rax, -24(%rbp)
	movq	-8(%rbp), %rax
	subq	-16(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-24(%rbp), %rax
	imulq	-32(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
