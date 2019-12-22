	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z8abs_jumpii          ## -- Begin function _Z8abs_jumpii
	.p2align	4, 0x90
__Z8abs_jumpii:                         ## @_Z8abs_jumpii
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
	cmpl	-8(%rbp), %esi
	jle	LBB0_2
## %bb.1:
	movl	-4(%rbp), %eax
	subl	-8(%rbp), %eax
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	jmp	LBB0_3
LBB0_2:
	movl	-8(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, -12(%rbp)         ## 4-byte Spill
LBB0_3:
	movl	-12(%rbp), %eax         ## 4-byte Reload
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
	subq	$96, %rsp
	movl	$0, -4(%rbp)
	leaq	-8(%rbp), %rdi
	movl	$1, %esi
	callq	__ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EEC1Ej
	movl	$2147483647, -12(%rbp)  ## imm = 0x7FFFFFFF
	callq	__ZNSt3__16chrono12system_clock3nowEv
	movq	%rax, -40(%rbp)
	leaq	-40(%rbp), %rdi
	callq	__ZNKSt3__16chrono10time_pointINS0_12system_clockENS0_8durationIxNS_5ratioILl1ELl1000000EEEEEE16time_since_epochEv
	movq	%rax, -32(%rbp)
	leaq	-32(%rbp), %rdi
	callq	__ZNSt3__16chronoL13duration_castINS0_8durationIxNS_5ratioILl1ELl1000EEEEExNS3_ILl1ELl1000000EEEEENS_9enable_ifIXsr13__is_durationIT_EE5valueES8_E4typeERKNS2_IT0_T1_EE
	movq	%rax, -24(%rbp)
	movl	$0, -44(%rbp)
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-44(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	LBB1_4
## %bb.2:                               ##   in Loop: Header=BB1_1 Depth=1
	movl	$1, %edi
	movl	$2, %esi
	callq	__Z8abs_jumpii
	movl	%eax, -76(%rbp)         ## 4-byte Spill
## %bb.3:                               ##   in Loop: Header=BB1_1 Depth=1
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
	jmp	LBB1_1
LBB1_4:
	callq	__ZNSt3__16chrono12system_clock3nowEv
	movq	%rax, -72(%rbp)
	leaq	-72(%rbp), %rdi
	callq	__ZNKSt3__16chrono10time_pointINS0_12system_clockENS0_8durationIxNS_5ratioILl1ELl1000000EEEEEE16time_since_epochEv
	movq	%rax, -64(%rbp)
	leaq	-64(%rbp), %rdi
	callq	__ZNSt3__16chronoL13duration_castINS0_8durationIxNS_5ratioILl1ELl1000EEEEExNS3_ILl1ELl1000000EEEEENS_9enable_ifIXsr13__is_durationIT_EE5valueES8_E4typeERKNS2_IT0_T1_EE
	movq	%rax, -56(%rbp)
	leaq	-56(%rbp), %rdi
	callq	__ZNKSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEE5countEv
	leaq	-24(%rbp), %rdi
	movq	%rax, -88(%rbp)         ## 8-byte Spill
	callq	__ZNKSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEE5countEv
	movq	__ZNSt3__14coutE@GOTPCREL(%rip), %rdi
	movq	-88(%rbp), %rcx         ## 8-byte Reload
	subq	%rax, %rcx
	movq	%rcx, %rsi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEx
	movq	%rax, %rdi
	leaq	__ZNSt3__1L4endlIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_(%rip), %rsi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEPFRS3_S4_E
	movl	-4(%rbp), %edx
	movq	%rax, -96(%rbp)         ## 8-byte Spill
	movl	%edx, %eax
	addq	$96, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EEC1Ej
__ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EEC1Ej: ## @_ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EEC1Ej
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rdi
	movl	-12(%rbp), %esi
	callq	__ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EEC2Ej
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNSt3__16chronoL13duration_castINS0_8durationIxNS_5ratioILl1ELl1000EEEEExNS3_ILl1ELl1000000EEEEENS_9enable_ifIXsr13__is_durationIT_EE5valueES8_E4typeERKNS2_IT0_T1_EE
__ZNSt3__16chronoL13duration_castINS0_8durationIxNS_5ratioILl1ELl1000EEEEExNS3_ILl1ELl1000000EEEEENS_9enable_ifIXsr13__is_durationIT_EE5valueES8_E4typeERKNS2_IT0_T1_EE: ## @_ZNSt3__16chronoL13duration_castINS0_8durationIxNS_5ratioILl1ELl1000EEEEExNS3_ILl1ELl1000000EEEEENS_9enable_ifIXsr13__is_durationIT_EE5valueES8_E4typeERKNS2_IT0_T1_EE
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rsi
	leaq	-24(%rbp), %rdi
	callq	__ZNKSt3__16chrono15__duration_castINS0_8durationIxNS_5ratioILl1ELl1000000EEEEENS2_IxNS3_ILl1ELl1000EEEEES6_Lb1ELb0EEclERKS5_
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNKSt3__16chrono10time_pointINS0_12system_clockENS0_8durationIxNS_5ratioILl1ELl1000000EEEEEE16time_since_epochEv
__ZNKSt3__16chrono10time_pointINS0_12system_clockENS0_8durationIxNS_5ratioILl1ELl1000000EEEEEE16time_since_epochEv: ## @_ZNKSt3__16chrono10time_pointINS0_12system_clockENS0_8durationIxNS_5ratioILl1ELl1000000EEEEEE16time_since_epochEv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	movq	(%rdi), %rdi
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNKSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEE5countEv
__ZNKSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEE5countEv: ## @_ZNKSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEE5countEv
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
	.p2align	4, 0x90         ## -- Begin function _ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EEC2Ej
__ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EEC2Ej: ## @_ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EEC2Ej
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rdi
	movl	-12(%rbp), %esi
	callq	__ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EE4seedEj
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EE4seedEj
__ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EE4seedEj: ## @_ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EE4seedEj
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rdi
	movl	-12(%rbp), %esi
	callq	__ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EE4seedENS_17integral_constantIbLb0EEENS2_IbLb1EEEj
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EE4seedENS_17integral_constantIbLb0EEENS2_IbLb1EEEj
__ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EE4seedENS_17integral_constantIbLb0EEENS2_IbLb1EEEj: ## @_ZNSt3__126linear_congruential_engineIjLj48271ELj0ELj2147483647EE4seedENS_17integral_constantIbLb0EEENS2_IbLb1EEEj
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	-24(%rbp), %rdi
	movl	-28(%rbp), %eax
	xorl	%edx, %edx
	movl	$2147483647, %esi       ## imm = 0x7FFFFFFF
	divl	%esi
	cmpl	$0, %edx
	movq	%rdi, -40(%rbp)         ## 8-byte Spill
	jne	LBB10_2
## %bb.1:
	movl	$1, %eax
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	jmp	LBB10_3
LBB10_2:
	movl	-28(%rbp), %eax
	xorl	%edx, %edx
	movl	$2147483647, %ecx       ## imm = 0x7FFFFFFF
	divl	%ecx
	movl	%edx, -44(%rbp)         ## 4-byte Spill
LBB10_3:
	movl	-44(%rbp), %eax         ## 4-byte Reload
	movq	-40(%rbp), %rcx         ## 8-byte Reload
	movl	%eax, (%rcx)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNKSt3__16chrono15__duration_castINS0_8durationIxNS_5ratioILl1ELl1000000EEEEENS2_IxNS3_ILl1ELl1000EEEEES6_Lb1ELb0EEclERKS5_
__ZNKSt3__16chrono15__duration_castINS0_8durationIxNS_5ratioILl1ELl1000000EEEEENS2_IxNS3_ILl1ELl1000EEEEES6_Lb1ELb0EEclERKS5_: ## @_ZNKSt3__16chrono15__duration_castINS0_8durationIxNS_5ratioILl1ELl1000000EEEEENS2_IxNS3_ILl1ELl1000EEEEES6_Lb1ELb0EEclERKS5_
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	-24(%rbp), %rdi
	callq	__ZNKSt3__16chrono8durationIxNS_5ratioILl1ELl1000000EEEE5countEv
	xorl	%ecx, %ecx
	movl	%ecx, %edx
	movl	$1000, %ecx             ## imm = 0x3E8
	movl	%ecx, %esi
	movq	%rdx, -40(%rbp)         ## 8-byte Spill
	cqto
	idivq	%rsi
	movq	%rax, -32(%rbp)
	leaq	-8(%rbp), %rdi
	leaq	-32(%rbp), %rsi
	movq	-40(%rbp), %rax         ## 8-byte Reload
	movq	%rax, %rdx
	callq	__ZNSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEEC1IxEERKT_PNS_9enable_ifIXaasr14is_convertibleIS6_xEE5valueooL_ZNS_17integral_constantIbLb0EE5valueEEntsr23treat_as_floating_pointIS6_EE5valueEvE4typeE
	movq	-8(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNKSt3__16chrono8durationIxNS_5ratioILl1ELl1000000EEEE5countEv
__ZNKSt3__16chrono8durationIxNS_5ratioILl1ELl1000000EEEE5countEv: ## @_ZNKSt3__16chrono8durationIxNS_5ratioILl1ELl1000000EEEE5countEv
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
	.p2align	4, 0x90         ## -- Begin function _ZNSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEEC1IxEERKT_PNS_9enable_ifIXaasr14is_convertibleIS6_xEE5valueooL_ZNS_17integral_constantIbLb0EE5valueEEntsr23treat_as_floating_pointIS6_EE5valueEvE4typeE
__ZNSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEEC1IxEERKT_PNS_9enable_ifIXaasr14is_convertibleIS6_xEE5valueooL_ZNS_17integral_constantIbLb0EE5valueEEntsr23treat_as_floating_pointIS6_EE5valueEvE4typeE: ## @_ZNSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEEC1IxEERKT_PNS_9enable_ifIXaasr14is_convertibleIS6_xEE5valueooL_ZNS_17integral_constantIbLb0EE5valueEEntsr23treat_as_floating_pointIS6_EE5valueEvE4typeE
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rdx
	callq	__ZNSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEEC2IxEERKT_PNS_9enable_ifIXaasr14is_convertibleIS6_xEE5valueooL_ZNS_17integral_constantIbLb0EE5valueEEntsr23treat_as_floating_pointIS6_EE5valueEvE4typeE
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZNSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEEC2IxEERKT_PNS_9enable_ifIXaasr14is_convertibleIS6_xEE5valueooL_ZNS_17integral_constantIbLb0EE5valueEEntsr23treat_as_floating_pointIS6_EE5valueEvE4typeE
__ZNSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEEC2IxEERKT_PNS_9enable_ifIXaasr14is_convertibleIS6_xEE5valueooL_ZNS_17integral_constantIbLb0EE5valueEEntsr23treat_as_floating_pointIS6_EE5valueEvE4typeE: ## @_ZNSt3__16chrono8durationIxNS_5ratioILl1ELl1000EEEEC2IxEERKT_PNS_9enable_ifIXaasr14is_convertibleIS6_xEE5valueooL_ZNS_17integral_constantIbLb0EE5valueEEntsr23treat_as_floating_pointIS6_EE5valueEvE4typeE
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
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	(%rsi), %rsi
	movq	%rsi, (%rdx)
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
	subq	$80, %rsp
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
	jmp	LBB15_1
LBB15_1:
	movsbl	-9(%rbp), %esi
Ltmp2:
	movq	-56(%rbp), %rdi         ## 8-byte Reload
	callq	__ZNKSt3__15ctypeIcE5widenEc
Ltmp3:
	movb	%al, -57(%rbp)          ## 1-byte Spill
	jmp	LBB15_2
LBB15_2:
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
	movb	-57(%rbp), %al          ## 1-byte Reload
	movsbl	%al, %eax
	addq	$80, %rsp
	popq	%rbp
	retq
LBB15_3:
Ltmp4:
	movl	%edx, %ecx
	movq	%rax, -32(%rbp)
	movl	%ecx, -36(%rbp)
Ltmp5:
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
Ltmp6:
	jmp	LBB15_4
LBB15_4:
	jmp	LBB15_5
LBB15_5:
	movq	-32(%rbp), %rdi
	callq	__Unwind_Resume
	ud2
LBB15_6:
Ltmp7:
	movq	%rax, %rdi
	movq	%rdx, -72(%rbp)         ## 8-byte Spill
	callq	___clang_call_terminate
Lfunc_end0:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table15:
Lexception0:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.uleb128 Lttbase0-Lttbaseref0
Lttbaseref0:
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
	.uleb128 Ltmp5-Ltmp3            ##   Call between Ltmp3 and Ltmp5
	.byte	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.uleb128 Ltmp5-Lfunc_begin0     ## >> Call Site 4 <<
	.uleb128 Ltmp6-Ltmp5            ##   Call between Ltmp5 and Ltmp6
	.uleb128 Ltmp7-Lfunc_begin0     ##     jumps to Ltmp7
	.byte	1                       ##   On action: 1
	.uleb128 Ltmp6-Lfunc_begin0     ## >> Call Site 5 <<
	.uleb128 Lfunc_end0-Ltmp6       ##   Call between Ltmp6 and Lfunc_end0
	.byte	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lcst_end0:
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
	.p2align	2
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
Lttbase0:
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
	.private_extern	___clang_call_terminate ## -- Begin function __clang_call_terminate
	.globl	___clang_call_terminate
	.weak_definition	___clang_call_terminate
	.p2align	4, 0x90
___clang_call_terminate:                ## @__clang_call_terminate
## %bb.0:
	pushq	%rax
	callq	___cxa_begin_catch
	movq	%rax, (%rsp)            ## 8-byte Spill
	callq	__ZSt9terminatev
                                        ## -- End function

.subsections_via_symbols
