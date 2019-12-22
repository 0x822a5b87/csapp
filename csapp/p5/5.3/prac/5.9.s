	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z5mergePKlS0_Pll      ## -- Begin function _Z5mergePKlS0_Pll
	.p2align	4, 0x90
__Z5mergePKlS0_Pll:                     ## @_Z5mergePKlS0_Pll
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	testq	%rcx, %rcx
	jle	LBB0_1
## %bb.10:
	xorl	%eax, %eax
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	.p2align	4, 0x90
LBB0_11:                                ## =>This Inner Loop Header: Depth=1
	movq	%r9, %r10
	movq	%rax, %r11
	movq	(%rdi,%rax,8), %r14
	movq	(%rsi,%r9,8), %rbx
	xorl	%r9d, %r9d
	xorl	%eax, %eax
	cmpq	%rbx, %r14
	setge	%r9b
	setl	%al
	cmovleq	%r14, %rbx
	movq	%rbx, (%rdx,%r8,8)
	incq	%r8
	addq	%r11, %rax
	addq	%r10, %r9
	cmpq	%rcx, %r9
	jge	LBB0_2
## %bb.12:                              ##   in Loop: Header=BB0_11 Depth=1
	cmpq	%rcx, %rax
	jl	LBB0_11
LBB0_2:
	cmpq	%rcx, %rax
	jl	LBB0_3
LBB0_6:
	cmpq	%rcx, %r9
	jl	LBB0_7
	jmp	LBB0_9
LBB0_1:
	xorl	%r8d, %r8d
	xorl	%r9d, %r9d
	xorl	%eax, %eax
	cmpq	%rcx, %rax
	jge	LBB0_6
LBB0_3:
	movq	%rcx, %r10
	subq	%rax, %r10
	leaq	(%rdi,%rax,8), %r11
	leaq	(%rdx,%r8,8), %r14
	addq	%rcx, %r8
	xorl	%ebx, %ebx
	.p2align	4, 0x90
LBB0_4:                                 ## =>This Inner Loop Header: Depth=1
	movq	(%r11,%rbx,8), %rdi
	movq	%rdi, (%r14,%rbx,8)
	incq	%rbx
	cmpq	%rbx, %r10
	jne	LBB0_4
## %bb.5:
	subq	%rax, %r8
	cmpq	%rcx, %r9
	jge	LBB0_9
LBB0_7:
	subq	%r9, %rcx
	leaq	(%rsi,%r9,8), %rax
	leaq	(%rdx,%r8,8), %rdx
	xorl	%esi, %esi
	.p2align	4, 0x90
LBB0_8:                                 ## =>This Inner Loop Header: Depth=1
	movq	(%rax,%rsi,8), %rdi
	movq	%rdi, (%rdx,%rsi,8)
	incq	%rsi
	cmpq	%rsi, %rcx
	jne	LBB0_8
LBB0_9:
	popq	%rbx
	popq	%r14
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
