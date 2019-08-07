	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z4proclPliPisPscPc    ## -- Begin function _Z4proclPliPisPscPc
	.p2align	4, 0x90
__Z4proclPliPisPscPc:                   ## @_Z4proclPliPisPscPc
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	.cfi_offset %rbx, -24
	movw	%r8w, %ax
	# 初始化 8 个参数
	movq	24(%rbp), %r10
	movb	16(%rbp), %r11b
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movq	%rcx, -40(%rbp)
	movw	%ax, -42(%rbp)
	movq	%r9, -56(%rbp)

    # *a1p += a1;
	movq	-16(%rbp), %rcx
	movq	-24(%rbp), %rsi
	addq	(%rsi), %rcx
	movq	%rcx, (%rsi)

	movl	-28(%rbp), %edx
	movq	-40(%rbp), %rcx
	addl	(%rcx), %edx
	movl	%edx, (%rcx)

	movswl	-42(%rbp), %edx
	movq	-56(%rbp), %rcx
	movswl	(%rcx), %r8d
	addl	%edx, %r8d
	movw	%r8w, %ax
	movw	%ax, (%rcx)

	movsbl	16(%rbp), %edx
	movq	24(%rbp), %rcx
	movsbl	(%rcx), %r8d
	addl	%edx, %r8d
	movb	%r8b, %bl
	movb	%bl, (%rcx)
	movb	%r11b, -57(%rbp)        ## 1-byte Spill
	movq	%r10, -72(%rbp)         ## 8-byte Spill
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
