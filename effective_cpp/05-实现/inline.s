	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z4add3iiiii           ## -- Begin function _Z4add3iiiii
	.p2align	4, 0x90
__Z4add3iiiii:                          ## @_Z4add3iiiii
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	-4(%rbp), %edi
	movl	-8(%rbp), %esi
	callq	__Z3addii
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %edi
	movl	-12(%rbp), %esi
	callq	__Z3addii
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %edi
	movl	-16(%rbp), %esi
	callq	__Z3addii
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %edi
	movl	-20(%rbp), %esi
	callq	__Z3addii
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z3addii               ## -- Begin function _Z3addii
	.weak_definition	__Z3addii
	.p2align	4, 0x90
__Z3addii:                              ## @_Z3addii
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %esi
	addl	-8(%rbp), %esi
	movl	%esi, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
