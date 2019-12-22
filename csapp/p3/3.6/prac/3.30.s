	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z7switch2i            ## -- Begin function _Z7switch2i
	.p2align	4, 0x90
__Z7switch2i:                           ## @_Z7switch2i
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %edi
	movl	%edi, %eax
	subl	$1, %eax
	movl	%edi, -8(%rbp)          ## 4-byte Spill
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	je	LBB0_1
	jmp	LBB0_5
LBB0_5:
	movl	-8(%rbp), %eax          ## 4-byte Reload
	subl	$3, %eax
	movl	%eax, -16(%rbp)         ## 4-byte Spill
	je	LBB0_2
	jmp	LBB0_3
LBB0_1:
	leaq	L_.str(%rip), %rdi
	movl	$1, %esi
	movb	$0, %al
	callq	_printf
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	jmp	LBB0_4
LBB0_2:
	leaq	L_.str(%rip), %rdi
	movl	$3, %esi
	movb	$0, %al
	callq	_printf
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	jmp	LBB0_4
LBB0_3:
	leaq	L_.str(%rip), %rdi
	movl	$4, %esi
	movb	$0, %al
	callq	_printf
	movl	%eax, -28(%rbp)         ## 4-byte Spill
LBB0_4:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d"


.subsections_via_symbols
