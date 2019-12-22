	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z8switcherlllPl       ## -- Begin function _Z8switcherlllPl
	.p2align	4, 0x90
__Z8switcherlllPl:                      ## @_Z8switcherlllPl
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-8(%rbp), %rcx
	movq	%rcx, %rdx
	subq	$7, %rdx
	movq	%rcx, -48(%rbp)         ## 8-byte Spill
	movq	%rdx, -56(%rbp)         ## 8-byte Spill
	ja	LBB0_5
## %bb.7:
	leaq	LJTI0_0(%rip), %rax
	movq	-48(%rbp), %rcx         ## 8-byte Reload
	movslq	(%rax,%rcx,4), %rdx
	addq	%rax, %rdx
	jmpq	*%rdx
LBB0_1:
	movq	-16(%rbp), %rax
	xorq	$15, %rax
	movq	%rax, -24(%rbp)
LBB0_2:
	movq	-24(%rbp), %rax
	addq	$112, %rax
	movq	%rax, -40(%rbp)
	jmp	LBB0_6
LBB0_3:
	movq	-16(%rbp), %rax
	addq	-24(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	shlq	$2, %rax
	movq	%rax, -40(%rbp)
	jmp	LBB0_6
LBB0_4:
	movq	-8(%rbp), %rax
	movq	%rax, -40(%rbp)
	jmp	LBB0_6
LBB1_5:
	movq	-16(%rbp), %rax
	movq	%rax, -40(%rbp)
LBB0_6:
	movq	-40(%rbp), %rax
	movq	-32(%rbp), %rcx
	movq	%rax, (%rcx)
	popq	%rbp
	retq
	.cfi_endproc
	.p2align	2, 0x90
	.data_region jt32
.set L0_0_set_2, LBB0_2-LJTI0_0
.set L0_0_set_5, LBB0_5-LJTI0_0
.set L0_0_set_3, LBB0_3-LJTI0_0
.set L0_0_set_4, LBB0_4-LJTI0_0
.set L0_0_set_1, LBB0_1-LJTI0_0
LJTI0_0:
	.long	L0_0_set_2
	.long	L0_0_set_5
	.long	L0_0_set_3
	.long	L0_0_set_5
	.long	L0_0_set_4
	.long	L0_0_set_1
	.long	L0_0_set_5
	.long	L0_0_set_3
	.end_data_region
                                        ## -- End function

.subsections_via_symbols
