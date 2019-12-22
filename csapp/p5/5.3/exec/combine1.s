	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z8combine1P7vec_recPl ## -- Begin function _Z8combine1P7vec_recPl
	.p2align	4, 0x90
__Z8combine1P7vec_recPl:                ## @_Z8combine1P7vec_recPl
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movq	$1, (%rsi)
	movq	$0, -24(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdi
	movq	%rax, -40(%rbp)         ## 8-byte Spill
	callq	__Z10vec_lengthP7vec_rec
	movq	-40(%rbp), %rdi         ## 8-byte Reload
	cmpq	%rax, %rdi
	jge	LBB0_4
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-8(%rbp), %rdi
	movq	-24(%rbp), %rsi
	leaq	-32(%rbp), %rdx
	callq	__Z15get_vec_elementP7vec_reclPl
	movq	-32(%rbp), %rdx
	movq	-16(%rbp), %rsi
	addq	(%rsi), %rdx
	movq	%rdx, (%rsi)
	movl	%eax, -44(%rbp)         ## 4-byte Spill
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -24(%rbp)
	jmp	LBB0_1
LBB0_4:
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z10vec_lengthP7vec_rec ## -- Begin function _Z10vec_lengthP7vec_rec
	.p2align	4, 0x90
__Z10vec_lengthP7vec_rec:               ## @_Z10vec_lengthP7vec_rec
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	(%rdi), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z15get_vec_elementP7vec_reclPl ## -- Begin function _Z15get_vec_elementP7vec_reclPl
	.p2align	4, 0x90
__Z15get_vec_elementP7vec_reclPl:       ## @_Z15get_vec_elementP7vec_reclPl
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	cmpq	$0, -24(%rbp)
	jl	LBB2_2
## %bb.1:
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rcx
	cmpq	(%rcx), %rax
	jl	LBB2_3
LBB2_2:
	movl	$0, -4(%rbp)
	jmp	LBB2_4
LBB2_3:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rcx
	movq	(%rax,%rcx,8), %rax
	movq	-32(%rbp), %rcx
	movq	%rax, (%rcx)
	movl	$1, -4(%rbp)
LBB2_4:
	movl	-4(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z7new_vecl            ## -- Begin function _Z7new_vecl
	.p2align	4, 0x90
__Z7new_vecl:                           ## @_Z7new_vecl
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$16, %eax
	movl	%eax, %ecx
	movq	%rdi, -16(%rbp)
	movq	%rcx, %rdi
	callq	_malloc
	movq	%rax, -24(%rbp)
	movq	$0, -32(%rbp)
	cmpq	$0, -24(%rbp)
	jne	LBB3_2
## %bb.1:
	movq	$0, -8(%rbp)
	jmp	LBB3_7
LBB3_2:
	cmpq	$0, -16(%rbp)
	jle	LBB3_6
## %bb.3:
	movl	$8, %eax
	movl	%eax, %esi
	movq	-16(%rbp), %rdi
	callq	_calloc
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	LBB3_5
## %bb.4:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	callq	_free
	movq	$0, -8(%rbp)
	jmp	LBB3_7
LBB3_5:
	movq	-16(%rbp), %rax
	movq	-24(%rbp), %rcx
	movq	%rax, (%rcx)
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	movq	%rax, 8(%rcx)
LBB3_6:
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
LBB3_7:
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
	subq	$112, %rsp
	xorl	%eax, %eax
	movl	%eax, %esi
	xorl	%eax, %eax
	movl	$16, %ecx
	movl	%ecx, %edx
	leaq	-16(%rbp), %rdi
	movq	%rdi, %r8
	movq	%rdi, -56(%rbp)         ## 8-byte Spill
	movq	%r8, %rdi
	movq	%rsi, -64(%rbp)         ## 8-byte Spill
	movl	%eax, %esi
	movq	%rdx, -72(%rbp)         ## 8-byte Spill
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	callq	_memset
	leaq	-32(%rbp), %rdx
	movq	%rdx, %rdi
	movl	-76(%rbp), %esi         ## 4-byte Reload
	movq	-72(%rbp), %rdx         ## 8-byte Reload
	callq	_memset
	movq	-56(%rbp), %rdi         ## 8-byte Reload
	movq	-64(%rbp), %rsi         ## 8-byte Reload
	callq	_gettimeofday
	movq	__ZNSt3__14coutE@GOTPCREL(%rip), %rdi
	movq	-16(%rbp), %rsi
	movl	%eax, -80(%rbp)         ## 4-byte Spill
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEl
	movq	%rax, %rdi
	leaq	__ZNSt3__1L4endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rsi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPFRS3_S4_E
	movl	$100000000, %ecx        ## imm = 0x5F5E100
	movl	%ecx, %edi
	movq	%rax, -88(%rbp)         ## 8-byte Spill
	callq	__Z7new_vecl
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rdi
	leaq	-48(%rbp), %rsi
	callq	__Z8combine1P7vec_recPl
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	leaq	-32(%rbp), %rdi
	callq	_gettimeofday
	movq	__ZNSt3__14coutE@GOTPCREL(%rip), %rdi
	movq	-32(%rbp), %rdx
	subq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, -92(%rbp)         ## 4-byte Spill
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEl
	movq	%rax, %rdi
	leaq	__ZNSt3__1L4endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rsi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPFRS3_S4_E
	xorl	%ecx, %ecx
	movq	%rax, -104(%rbp)        ## 8-byte Spill
	movl	%ecx, %eax
	addq	$112, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPFRS3_S4_E
__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPFRS3_S4_E: ## @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPFRS3_S4_E
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdi
	callq	*-16(%rbp)
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNSt3__1L4endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_
__ZNSt3__1L4endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_: ## @_ZNSt3__1L4endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rax
	movq	%rdi, -16(%rbp)         ## 8-byte Spill
	movq	%rax, %rdi
	movl	$10, %esi
	callq	__ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5widenEc
	movq	-16(%rbp), %rdi         ## 8-byte Reload
	movsbl	%al, %esi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE3putEc
	movq	-8(%rbp), %rdi
	movq	%rax, -24(%rbp)         ## 8-byte Spill
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE5flushEv
	movq	-8(%rbp), %rcx
	movq	%rax, -32(%rbp)         ## 8-byte Spill
	movq	%rcx, %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5widenEc
__ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5widenEc: ## @_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5widenEc
Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception0
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movb	%sil, %al
	movq	%rdi, -8(%rbp)
	movb	%al, -9(%rbp)
	movq	-8(%rbp), %rsi
	leaq	-24(%rbp), %rdi
	movq	%rdi, -48(%rbp)         ## 8-byte Spill
	callq	__ZNKSt3__18ios_base6getlocEv
Ltmp0:
	movq	-48(%rbp), %rdi         ## 8-byte Reload
	callq	__ZNSt3__1L9use_facetINS_5ctypeIcEEEERKT_RKNS_6localeE
Ltmp1:
	movq	%rax, -56(%rbp)         ## 8-byte Spill
	jmp	LBB7_1
LBB7_1:
	movsbl	-9(%rbp), %esi
Ltmp2:
	movq	-56(%rbp), %rdi         ## 8-byte Reload
	callq	__ZNKSt3__15ctypeIcE5widenEc
Ltmp3:
	movb	%al, -57(%rbp)          ## 1-byte Spill
	jmp	LBB7_2
LBB7_2:
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
	movb	-57(%rbp), %al          ## 1-byte Reload
	movsbl	%al, %eax
	addq	$64, %rsp
	popq	%rbp
	retq
LBB7_3:
Ltmp4:
	movl	%edx, %ecx
	movq	%rax, -32(%rbp)
	movl	%ecx, -36(%rbp)
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
## %bb.4:
	movq	-32(%rbp), %rdi
	callq	__Unwind_Resume
	ud2
Lfunc_end0:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table7:
Lexception0:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	255                     ## @TType Encoding = omit
	.byte	1                       ## Call site Encoding = uleb128
	.uleb128 Lcst_end0-Lcst_begin0
Lcst_begin0:
	.uleb128 Lfunc_begin0-Lfunc_begin0 ## >> Call Site 1 <<
	.uleb128 Ltmp0-Lfunc_begin0     ##   Call between Lfunc_begin0 and Ltmp0
	.byte	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.uleb128 Ltmp0-Lfunc_begin0     ## >> Call Site 2 <<
	.uleb128 Ltmp3-Ltmp0            ##   Call between Ltmp0 and Ltmp3
	.uleb128 Ltmp4-Lfunc_begin0     ##     jumps to Ltmp4
	.byte	0                       ##   On action: cleanup
	.uleb128 Ltmp3-Lfunc_begin0     ## >> Call Site 3 <<
	.uleb128 Lfunc_end0-Ltmp3       ##   Call between Ltmp3 and Lfunc_end0
	.byte	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lcst_end0:
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.p2align	4, 0x90         ## -- Begin function _ZNSt3__1L9use_facetINS_5ctypeIcEEEERKT_RKNS_6localeE
__ZNSt3__1L9use_facetINS_5ctypeIcEEEERKT_RKNS_6localeE: ## @_ZNSt3__1L9use_facetINS_5ctypeIcEEEERKT_RKNS_6localeE
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	__ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rsi
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	__ZNKSt3__16locale9use_facetERNS0_2idE
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNKSt3__15ctypeIcE5widenEc
__ZNKSt3__15ctypeIcE5widenEc:           ## @_ZNKSt3__15ctypeIcE5widenEc
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movb	%sil, %al
	movq	%rdi, -8(%rbp)
	movb	%al, -9(%rbp)
	movq	-8(%rbp), %rdi
	movb	-9(%rbp), %al
	movq	(%rdi), %rcx
	movsbl	%al, %esi
	callq	*56(%rcx)
	movsbl	%al, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
