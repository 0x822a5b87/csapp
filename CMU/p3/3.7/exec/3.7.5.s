	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z1fv                  ## -- Begin function _Z1fv
	.p2align	4, 0x90
__Z1fv:                                 ## @_Z1fv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	$1, -8(%rbp)
	movl	$2, -12(%rbp)
	leaq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	leaq	-12(%rbp), %rax
	movq	%rax, -32(%rbp)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
