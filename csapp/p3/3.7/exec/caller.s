
  subq	$32, %rsp
  movq	$534, -8(%rbp)          ## imm = 0x216
  movq	$1057, -16(%rbp)        ## imm = 0x421
  leaq	-8(%rbp), %rdi
  leaq	-16(%rbp), %rsi
  callq	__Z8swap_andPlS_
  movq	%rax, -24(%rbp)
  movq	-8(%rbp), %rax
  subq	-16(%rbp), %rax
  movq	%rax, -32(%rbp)
  movq	-24(%rbp), %rax
  imulq	-32(%rbp), %rax
  addq	$32, %rsp
  popq	%rbp
  retq
