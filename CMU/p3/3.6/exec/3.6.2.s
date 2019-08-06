	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z5testqv              ## -- Begin function _Z5testqv
	.p2align	4, 0x90
__Z5testqv:                             ## @_Z5testqv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$0, -4(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jne	LBB0_2
## %bb.1:
	jmp	LBB0_2
LBB0_2:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
