	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z7test_ifi            ## -- Begin function _Z7test_ifi
	.p2align	4, 0x90
__Z7test_ifi:                           ## @_Z7test_ifi
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$0, -4(%rbp)
	je	LBB0_2
## %bb.1:
	movl	-4(%rbp), %esi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -8(%rbp)          ## 4-byte Spill
	jmp	LBB0_3
LBB0_2:
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -12(%rbp)         ## 4-byte Spill
LBB0_3:
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"x = %d"

L_.str.1:                               ## @.str.1
	.asciz	"x = 0"


.subsections_via_symbols
