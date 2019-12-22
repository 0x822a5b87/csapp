    .text
    .globl  push_test

_main:
    call push_test

push_test:
    movq    %rsp, %rax
    pushq   %rsp
    popq    %rdx
    subq    %rdx, %rax

    ret
