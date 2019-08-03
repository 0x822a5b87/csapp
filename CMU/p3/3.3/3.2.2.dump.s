_multstore:
       0:	55 	pushq	%rbp
       1:	48 89 e5 	movq	%rsp, %rbp
       4:	53 	pushq	%rbx
       5:	50 	pushq	%rax
       6:	48 89 d3 	movq	%rdx, %rbx
       9:	e8 00 00 00 00 	callq	0 <_multstore+0xe>
       e:	48 89 03 	movq	%rax, (%rbx)
      11:	48 83 c4 08 	addq	$8, %rsp
      15:	5b 	popq	%rbx
      16:	5d 	popq	%rbp
      17:	c3 	retq
