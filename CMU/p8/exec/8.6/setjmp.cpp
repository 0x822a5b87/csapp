//
// Created by 杜航宇 on 2019/11/30.
//

#include <csetjmp>
#include "iostream"

jmp_buf buf;

int error1 = 0;
int error2 = 1;

void foo(void), bar(void);

// setjmp 会返回两次
// 第一次返回0，我们随后执行 foo()
// 如果在 foo() 和 bar() 中我们碰到一个错误，那么会立马通过 longjmp 返回到 setjmp(buf) 的位置
// 并且进行后续的 switch 条件判断
int main()
{
    switch(setjmp(buf))
    {
        case 0:
            foo();
            break;
        case 1:
            printf("detected an error1 condition in foo\n");
            break;
        case 2:
            printf("detected an error1 condition in foo\n");
            break;
        default:
            printf("Unknown error condition in foo\n");
    }
    exit(0);
}

void foo(void)
{
    if (error1)
        longjmp(buf, 1);
    bar();
}

void bar(void)
{
    if (error2)
        longjmp(buf, 2);
}
