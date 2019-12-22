	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z9many_argsmmmmmmmm   ## -- Begin function _Z9many_argsmmmmmmmm
	.p2align	4, 0x90
__Z9many_argsmmmmmmmm:                  ## @_Z9many_argsmmmmmmmm
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	24(%rbp), %rax
	movq	16(%rbp), %r10
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r9, -48(%rbp)
	movq	%r10, -56(%rbp)         ## 8-byte Spill
	movq	%rax, -64(%rbp)         ## 8-byte Spill
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z14call_many_argsv    ## -- Begin function _Z14call_many_argsv
	.p2align	4, 0x90
__Z14call_many_argsv:                   ## @_Z14call_many_argsv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$1, %eax
	movl	%eax, %edi
	movl	$2, %eax
	movl	%eax, %esi
	movl	$3, %eax
	movl	%eax, %edx
	movl	$4, %eax
	movl	%eax, %ecx
	movl	$5, %eax
	movl	%eax, %r8d
	movl	$6, %eax
	movl	%eax, %r9d
	movl	$7, %eax
	movl	%eax, %r10d
	movl	$8, %eax
	movl	%eax, %r11d
	movq	$7, (%rsp)
	movq	$8, 8(%rsp)
	movq	%r11, -8(%rbp)          ## 8-byte Spill
	movq	%r10, -16(%rbp)         ## 8-byte Spill
	callq	__Z9many_argsmmmmmmmm
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z1qv                  ## -- Begin function _Z1qv
	.p2align	4, 0x90
__Z1qv:                                 ## @_Z1qv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$1, -4(%rbp)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z1pv                  ## -- Begin function _Z1pv
	.p2align	4, 0x90
__Z1pv:                                 ## @_Z1pv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	callq	__Z1qv
	movl	$0, -4(%rbp)
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
