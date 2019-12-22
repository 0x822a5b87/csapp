sum:
    movl    $0, %eax
    testq   %rdi
    jle     .L9
    pushq   %rbx

    movq    (%rdi), %rbx
    subq    $1, %rsi
    addq    $8, %rdi
    call    sum
    addq    %rbx, %rax

    popq     %rbx
.L9:
    rep
    ret
