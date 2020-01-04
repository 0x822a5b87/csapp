#include "../apue.h"
#include "setjmp.h"

static void f1(int, int, int, int);

static void f2(void);

// 一般我们把 jmp_buf 设置为全局变量
static jmp_buf jmpbuffer;
static int     globval;

int main(int argc, char **argv)
{
    int          autoval;
    register int regival;
    volatile int volaval;
    static int   statval;

    globval = 1;
    autoval = 2;
    regival = 3;
    volaval = 4;
    statval = 5;

    // setjmp 类似于 fork()，当返回值不为 0 的时候说明是通过 longjmp 跳转回来的
    if (setjmp(jmpbuffer) != 0)
    {
        printf("after longjmp:\n");
        printf("global value = %d, auto val = %d, regival = %d"
               " volaval = %d, statval = %d\n", globval, autoval, regival, volaval, statval);
        exit(0);
    }

    globval = 95;
    autoval = 96;
    regival = 97;
    volaval = 98;
    statval = 99;

    f1(autoval, regival, volaval, statval);
    exit(0);
}

static void f1(int i, int j, int k, int l)
{
    printf("in f1():\n");
    printf("global value = %d, auto val = %d, regival = %d"
           " volaval = %d, statval = %d\n", globval, i, j, k, l);
    f2();
}

static void f2(void)
{
    // longjmp 的第二个参数就是 setjmp 的返回值
    longjmp(jmpbuffer, 1);
}
