	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z3sumPll              ## -- Begin function _Z3sumPll
	.p2align	4, 0x90
__Z3sumPll:                             ## @_Z3sumPll
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jg	LBB0_2
## %bb.1:
	movq	$0, -8(%rbp)
	jmp	LBB0_3
LBB0_2:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rcx
	addq	$8, %rcx
	movq	-24(%rbp), %rdx
	subq	$1, %rdx
	movq	%rcx, %rdi
	movq	%rdx, %rsi
	movq	%rax, -32(%rbp)         ## 8-byte Spill
	callq	__Z3sumPll
	movq	-32(%rbp), %rcx         ## 8-byte Reload
	addq	%rax, %rcx
	movq	%rcx, -8(%rbp)
LBB0_3:
	movq	-8(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movl	$5, %eax
	movl	%eax, %esi
	leaq	-48(%rbp), %rcx
	xorl	%eax, %eax
	movl	$40, %edx
                                        ## kill: def $rdx killed $edx
	movq	___stack_chk_guard@GOTPCREL(%rip), %rdi
	movq	(%rdi), %rdi
	movq	%rdi, -8(%rbp)
	movq	%rcx, %rdi
	movq	%rsi, -56(%rbp)         ## 8-byte Spill
	movl	%eax, %esi
	movq	%rcx, -64(%rbp)         ## 8-byte Spill
	callq	_memset
	movq	$1, -48(%rbp)
	movq	$2, -40(%rbp)
	movq	$3, -32(%rbp)
	movq	$4, -24(%rbp)
	movq	$5, -16(%rbp)
	movq	-64(%rbp), %rdi         ## 8-byte Reload
	movq	-56(%rbp), %rsi         ## 8-byte Reload
	callq	__Z3sumPll
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	jne	LBB1_2
## %bb.1:
	xorl	%eax, %eax
	addq	$80, %rsp
	popq	%rbp
	retq
LBB1_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
