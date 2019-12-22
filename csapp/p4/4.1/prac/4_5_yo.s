absSum:
    irmovq  0x8, %r8                # constant 8
    irmovq  0x1, %r9                # constant 1
    xorq    %rax, %rax              # set %rax 0
    andq    %rsi, %rsi
    jmp      test

loop:
    mrmovq  (%rsi), %r10            # x = *start
    xorq    %r11, %r11              # constant 0
    subq    %r10, %r11              # x = -x
    jle     add                     # jump if -x <= 0
    rrmovq  %r11, %r10

add:
    addq    %r10, %rax
    addq    %r8, %rdi
    subq    %r9, %rsi

test:
    jne loop
    ret
