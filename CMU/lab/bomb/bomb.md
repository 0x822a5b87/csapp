# 执行

## phase_1

1. 直接反汇编 `phase_1` 得到

```asm
phase_1:
  400ee0:	48 83 ec 08 	subq	$8, %rsp
  400ee4:	be 00 24 40 00 	movl	$4203520, %esi
  400ee9:	e8 4a 04 00 00 	callq	1098 <strings_not_equal>
  400eee:	85 c0 			testl	%eax, %eax
  400ef0:	74 05 			je	5 	<phase_1+0x17>
  400ef2:	e8 43 05 00 00 	callq	1347 <explode_bomb>
  400ef7:	48 83 c4 08 	addq	$8, %rsp
  400efb:	c3 	retq
```

结合我们在 c 语言中调用了 

```c
    input = read_line();
    phase_1(input);
    phase_defused();
```

1. 由于 `phase_1` 中的 input 被读取到第一个参数 `%rdi`，所以在 phase_1 中我们直接初始化第二个参数 `%esi`。
2. 我们可以通过 `x/s $rsi` 来输出第一个寄存器中的内容
3. phase_1 就是调用 `strings_not_equal` 方法来对比 %rdi 和 %rsi 两个参数是否一致

```asm
strings_not_equal:
  401338:	41 54 				pushq	%r12
  40133a:	55 					pushq	%rbp
  40133b:	53 					pushq	%rbx
  40133c:	48 89 fb 			movq	%rdi, %rbx
  40133f:	48 89 f5 			movq	%rsi, %rbp
  401342:	e8 d4 ff ff ff 		callq	-44 <string_length>
  401347:	41 89 c4 			movl	%eax, %r12d
  40134a:	48 89 ef 			movq	%rbp, %rdi
  40134d:	e8 c9 ff ff ff 		callq	-55 <string_length>
  401352:	ba 01 00 00 00 		movl	$1, %edx
  401357:	41 39 c4 			cmpl	%eax, %r12d
  40135a:	75 3f 				jne	63 <strings_not_equal+0x63>
  40135c:	0f b6 03 			movzbl	(%rbx), %eax
  40135f:	84 c0 				testb	%al, %al
  401361:	74 25 				je	37 <strings_not_equal+0x50>
  401363:	3a 45 00 			cmpb	(%rbp), %al
  401366:	74 0a 				je	10 <strings_not_equal+0x3a>
  401368:	eb 25 				jmp	37 <strings_not_equal+0x57>
  40136a:	3a 45 00 			cmpb	(%rbp), %al
  40136d:	0f 1f 00 			nopl	(%rax)
  401370:	75 24 				jne	36 <strings_not_equal+0x5e>
  401372:	48 83 c3 01 		addq	$1, %rbx
  401376:	48 83 c5 01 		addq	$1, %rbp
  40137a:	0f b6 03 			movzbl	(%rbx), %eax
  40137d:	84 c0 				testb	%al, %al
  40137f:	75 e9 				jne	-23 <strings_not_equal+0x32>
  401381:	ba 00 00 00 00 		movl	$0, %edx
  401386:	eb 13 				jmp	19 <strings_not_equal+0x63>
  401388:	ba 00 00 00 00 		movl	$0, %edx
  40138d:	eb 0c 				jmp	12 <strings_not_equal+0x63>
  40138f:	ba 01 00 00 00 		movl	$1, %edx
  401394:	eb 05 				jmp	5 <strings_not_equal+0x63>
  401396:	ba 01 00 00 00 		movl	$1, %edx
  40139b:	89 d0 				movl	%edx, %eax
  40139d:	5b 					popq	%rbx
  40139e:	5d 					popq	%rbp
  40139f:	41 5c 				popq	%r12
  4013a1:	c3 					retq
```

### string_length

```asm
   0x000000000040131b <+0>:     cmpb   $0x0,(%rdi)							// 比较参数1是否为 null
   0x000000000040131e <+3>:     je     0x401332 <string_length+23>			// 如果为 null 则返回 0
   0x0000000000401320 <+5>:     mov    %rdi,%rdx							// 存 %rdi 到 %rdx
   0x0000000000401323 <+8>:     add    $0x1,%rdx							// rdx += 1，这个时候 rdx 是一个指针，相当于我们把指针前移了一位
   0x0000000000401327 <+12>:    mov    %edx,%eax							// 复制 rdx 到 eax
   0x0000000000401329 <+14>:    sub    %edi,%eax							// rdx - edi，相当于用我们移动之后的指针 - 移动之前的指针，自然就是我们的字符串长度
   0x000000000040132b <+16>:    cmpb   $0x0,(%rdx)							// 
   0x000000000040132e <+19>:    jne    0x401323 <string_length+8>			// 
   0x0000000000401330 <+21>:    repz retq 
   0x0000000000401332 <+23>:    mov    $0x0,%eax
   0x0000000000401337 <+28>:    retq  
```

```c++
size_t string_length2(char *ptr)
{
    if (ptr == nullptr)
    {
        return 0u;
    }
    char *tmp = ptr;
    while (*tmp != '\0')
    {
        ++tmp;
    }
    return tmp - ptr;
}
```

## phase_2

1. 在 read_six_numbers 函数中，我们将六个数组依次读取到了 %rsi, %rsi + 4, %rsi + 8, %rsi + c, %rsi + 10, %rsi + 14。而 %rsi == %rsp
2. 

```asm
Dump of assembler code for function phase_2:
=> 0x0000000000400efc <+0>:     push   %rbp
   0x0000000000400efd <+1>:     push   %rbx
   0x0000000000400efe <+2>:     sub    $0x28,%rsp							// 开辟函数栈

   // 开始函数逻辑
   0x0000000000400f02 <+6>:     mov    %rsp,%rsi							// 保存 %rsp，因为 %rsp 在函数 read_six_numbers 中使用这个地址。
   0x0000000000400f05 <+9>:     callq  0x40145c <read_six_numbers>
   0x0000000000400f0a <+14>:    cmpl   $0x1,(%rsp)							// 比较 %rsp 指向的值是否为 1
   0x0000000000400f0e <+18>:    je     0x400f30 <phase_2+52>				// 如果等于 1 则跳转到 52
   0x0000000000400f10 <+20>:    callq  0x40143a <explode_bomb>				// 否则引爆炸弹
   0x0000000000400f15 <+25>:    jmp    0x400f30 <phase_2+52>

   // 27
   // 这段代码判断数组中的当前数字是否为上一个数字的二倍
   0x0000000000400f17 <+27>:    mov    -0x4(%rbx),%eax						// 现在 (%rbx) 指向栈中的下个数字
   0x0000000000400f1a <+30>:    add    %eax,%eax
   0x0000000000400f1c <+32>:    cmp    %eax,(%rbx)							// 判断 %rbx 是否等于 %eax + %eax
   0x0000000000400f1e <+34>:    je     0x400f25 <phase_2+41>
   0x0000000000400f20 <+36>:    callq  0x40143a <explode_bomb>

   // 41
   // 判定循环条件，相当于 for (int i = 0; i < 6; ++i)
   // 所以在 52 中它指向最后一个数字的后一位
   0x0000000000400f25 <+41>:    add    $0x4,%rbx
   0x0000000000400f29 <+45>:    cmp    %rbp,%rbx							// 比较循环现在是否已经结束，如果指针已经指向数组中最后一个数字的后一位那么跳出循环
   0x0000000000400f2c <+48>:    jne    0x400f17 <phase_2+27>
   0x0000000000400f2e <+50>:    jmp    0x400f3c <phase_2+64>

   // 52
   0x0000000000400f30 <+52>:    lea    0x4(%rsp),%rbx						// 52	%rsp 指针指向下一个数字
   0x0000000000400f35 <+57>:    lea    0x18(%rsp),%rbp						// 设置指针地址为数组的最后一个数字的后一位
   0x0000000000400f3a <+62>:    jmp    0x400f17 <phase_2+27>

   // 64
   0x0000000000400f3c <+64>:    add    $0x28,%rsp
   0x0000000000400f40 <+68>:    pop    %rbx
   0x0000000000400f41 <+69>:    pop    %rbp
   0x0000000000400f42 <+70>:    retq 
```

#### read_six_numbers

1. `sscanf` 这个函数接受不定长度的参数，第一个参数和第二个参数是 `const char *`，后面的参数长度不定。
2. 在上层函数 `phase_2` 中，它先将 `mov %rsp, %rsi` 并且在调用之后通过 `cmpl $0x1,(%rsp)` 进行了比较。所以在本函数中，我们把 %rdx 赋值了 %rsi 就是说我们通过 `sscanf` 初始化了第三个参数
3. 所以这个函数的整个过程都是在初始化 `sscanf` 的八个参数，我们通过 `break sscanf` 下打断点。随后通过 `x/s $rdi` 和 `x/s $rsi` 查看参数可以知道 `0x6037d0 <input_strings+80>:     "1 2 4 8 16 32"` 和 `0x4025c3:        "%d %d %d %d %d %d"`。于是我们知道了我们的六个寄存器被初始化为了什么值。


```asm
   0x000000000040145c <+0>:     sub    $0x18,%rsp									// 开辟函数栈
   0x0000000000401460 <+4>:     mov    %rsi,%rdx									// 参数3地址指向 rsi
   0x0000000000401463 <+7>:     lea    0x4(%rsi),%rcx								// 赋值参数4

   // 由于 x86 在函数调用中只支持 6 个寄存器，所以有一部分值我们存放到栈中
   0x0000000000401467 <+11>:    lea    0x14(%rsi),%rax								// 将寄存器赋值为 %rsi + 10 和 %rsi + 14
   0x000000000040146b <+15>:    mov    %rax,0x8(%rsp)								
   0x0000000000401470 <+20>:    lea    0x10(%rsi),%rax
   0x0000000000401474 <+24>:    mov    %rax,(%rsp)

   0x0000000000401478 <+28>:    lea    0xc(%rsi),%r9								// 赋值参数6
   0x000000000040147c <+32>:    lea    0x8(%rsi),%r8								// 赋值参数5
   0x0000000000401480 <+36>:    mov    $0x4025c3,%esi								// 赋值参数2
   0x0000000000401485 <+41>:    mov    $0x0,%eax									// 初始化参数返回值

   0x000000000040148a <+46>:    callq  0x400bf0 <__isoc99_sscanf@plt>				// 调用 sscanf
   0x000000000040148f <+51>:    cmp    $0x5,%eax									// 最少需要读取到 6 个参数，否则直接引爆炸弹
   0x0000000000401492 <+54>:    jg     0x401499 <read_six_numbers+61>
   0x0000000000401494 <+56>:    callq  0x40143a <explode_bomb>

   0x0000000000401499 <+61>:    add    $0x18,%rsp									// 还原函数栈
   0x000000000040149d <+65>:    retq												// 返回
```

## phase_3

1. 这里需要输入两个数字，第一个数字指示我们会跳转到 switch 的哪个语句块。在这个语句块中，我们会为 %eax 赋值。随后我们会比较 %eax 和我们输入的第二个参数，如果两个参数相同那么拆弹成功
2. 这题的答案有多个，根据 switch 语句的不同我们的第二个参数也是不同的

```asm
=> 0x0000000000400f43 <+0>:		sub    $0x18,%rsp

   0x0000000000400f47 <+4>:		lea    0xc(%rsp),%rcx						// 初始化参数4，也就是我们输入的第二个数字
   0x0000000000400f4c <+9>:		lea    0x8(%rsp),%rdx						// 初始化参数3，也就是我们输入的第一个数字
   0x0000000000400f51 <+14>:	mov    $0x4025cf,%esi
   0x0000000000400f56 <+19>:	mov    $0x0,%eax
   0x0000000000400f5b <+24>:	callq  0x400bf0 <__isoc99_sscanf@plt>		// 使用 sscanf 初始化两个参数
   0x0000000000400f60 <+29>:	cmp    $0x1,%eax							// 如果读取到一个以上的数字则跳转，否则引爆炸弹
   0x0000000000400f63 <+32>:	jg     0x400f6a <phase_3+39>
   0x0000000000400f65 <+34>:	callq  0x40143a <explode_bomb>

   // 39
   0x0000000000400f6a <+39>:	cmpl   $0x7,0x8(%rsp)
   0x0000000000400f6f <+44>:	ja     0x400fad <phase_3+106>				// 如果输入的第一个数字大于7则直接到引爆炸弹

   0x0000000000400f71 <+46>:	mov    0x8(%rsp),%eax
   // (gdb) x/x 0x402470
   // 0x402470:       0x00400f7c
   0x0000000000400f75 <+50>:	jmpq   *0x402470(,%rax,8)

   // switch 语句
   0x0000000000400f7c <+57>:	mov    $0xcf,%eax
   0x0000000000400f81 <+62>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f83 <+64>:	mov    $0x2c3,%eax
   0x0000000000400f88 <+69>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f8a <+71>:	mov    $0x100,%eax
   0x0000000000400f8f <+76>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f91 <+78>:	mov    $0x185,%eax
   0x0000000000400f96 <+83>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f98 <+85>:	mov    $0xce,%eax
   0x0000000000400f9d <+90>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f9f <+92>:	mov    $0x2aa,%eax
   0x0000000000400fa4 <+97>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400fa6 <+99>:	mov    $0x147,%eax
   0x0000000000400fab <+104>:	jmp    0x400fbe <phase_3+123>

   // 106
   // 引爆炸弹
   0x0000000000400fad <+106>:	callq  0x40143a <explode_bomb>
   0x0000000000400fb2 <+111>:	mov    $0x0,%eax
   0x0000000000400fb7 <+116>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400fb9 <+118>:	mov    $0x137,%eax
   
   0x0000000000400fbe <+123>:	cmp    0xc(%rsp),%eax						// 比较第二个参数和我们在 switch 语句中初始化的值
   0x0000000000400fc2 <+127>:	je     0x400fc9 <phase_3+134>

   0x0000000000400fc4 <+129>:	callq  0x40143a <explode_bomb>

   0x0000000000400fc9 <+134>:	add    $0x18,%rsp
   0x0000000000400fcd <+138>:	retq
```

## phase_4

```asm
=> 0x000000000040100c <+0>:     sub    $0x18,%rsp

   // 还是熟悉的通过 sscanf 初始化两个参数
   0x0000000000401010 <+4>:     lea    0xc(%rsp),%rcx						// 第二个输入参数
   0x0000000000401015 <+9>:     lea    0x8(%rsp),%rdx						// 第一个输入参数
   0x000000000040101a <+14>:    mov    $0x4025cf,%esi
   0x000000000040101f <+19>:    mov    $0x0,%eax
   0x0000000000401024 <+24>:    callq  0x400bf0 <__isoc99_sscanf@plt>
   0x0000000000401029 <+29>:    cmp    $0x2,%eax
   0x000000000040102c <+32>:    jne    0x401035 <phase_4+41>				// 如果初始化参数数量不等于2则引爆炸弹

   0x000000000040102e <+34>:    cmpl   $0xe,0x8(%rsp)						// 如果第一个参数大于 0xe 则引爆炸弹
   0x0000000000401033 <+39>:    jbe    0x40103a <phase_4+46>
   0x0000000000401035 <+41>:    callq  0x40143a <explode_bomb>

   0x000000000040103a <+46>:    mov    $0xe,%edx							// 初始化参数3
   0x000000000040103f <+51>:    mov    $0x0,%esi							// 初始化参数2
   0x0000000000401044 <+56>:    mov    0x8(%rsp),%edi						// 初始化参数1
   0x0000000000401048 <+60>:    callq  0x400fce <func4>

   0x000000000040104d <+65>:    test   %eax,%eax							// 如果 func4 的返回值不为0，或者第二个参数不为 0 则引爆炸弹
   0x000000000040104f <+67>:    jne    0x401058 <phase_4+76>
   0x0000000000401051 <+69>:    cmpl   $0x0,0xc(%rsp)						// 注意，我们这里将栈指针做为参数调用 func4，所以 func4 可能会修改我们输入参数的值
   0x0000000000401056 <+74>:    je     0x40105d <phase_4+81>
   0x0000000000401058 <+76>:    callq  0x40143a <explode_bomb>

   0x000000000040105d <+81>:    add    $0x18,%rsp
   0x0000000000401061 <+85>:    retq 
```

### func4

1. 假设 func4 的输入参数为 x, y, z。z = 14, y = 0;

```asm
=> 0x0000000000400fce <+0>:     sub    $0x8,%rsp

   // eax
   0x0000000000400fd2 <+4>:     mov    %edx,%eax					// eax = z
   0x0000000000400fd4 <+6>:     sub    %esi,%eax					// eax = z - y

   // ecx
   0x0000000000400fd6 <+8>:     mov    %eax,%ecx					// ecx = z - y
   0x0000000000400fd8 <+10>:    shr    $0x1f,%ecx					// 保留 ecx 的最高位，假设为 h

   // eax
   0x0000000000400fdb <+13>:    add    %ecx,%eax					// eax = z - y + h
   0x0000000000400fdd <+15>:    sar    %eax							// eax = (z - y + h) / 2

   0x0000000000400fdf <+17>:    lea    (%rax,%rsi,1),%ecx			// ecx = (z + y + h) / 2
   0x0000000000400fe2 <+20>:    cmp    %edi,%ecx					// 比较 ecx 和 x
   0x0000000000400fe4 <+22>:    jle    0x400ff2 <func4+36>			// 如果 x >= (z + y + h) / 2 则跳转

   0x0000000000400fe6 <+24>:    lea    -0x1(%rcx),%edx				// edx = (z + y + h) / 2 - 1
   0x0000000000400fe9 <+27>:    callq  0x400fce <func4>				// func4(x, y, (z + y + h) / 2 - 1)
   0x0000000000400fee <+32>:    add    %eax,%eax					// eax = 2 * (z - y + h)
   0x0000000000400ff0 <+34>:    jmp    0x401007 <func4+57>

   // 36
   0x0000000000400ff2 <+36>:    mov    $0x0,%eax					// 
   0x0000000000400ff7 <+41>:    cmp    %edi,%ecx
   0x0000000000400ff9 <+43>:    jge    0x401007 <func4+57>
   0x0000000000400ffb <+45>:    lea    0x1(%rcx),%esi
   0x0000000000400ffe <+48>:    callq  0x400fce <func4>
   0x0000000000401003 <+53>:    lea    0x1(%rax,%rax,1),%eax
   
	// 57 退出函数
   0x0000000000401007 <+57>:    add    $0x8,%rsp
   0x000000000040100b <+61>:    retq  
```

### func4 代码

14 = 8 + 4 + 2

0x01110

```c++
int func4(int *x, int y, int z)
{
	int eax = z - y;
	int ecx = eax >>> 0x1f;
	ax += ecx;
	eax >>= 1;
}
```
