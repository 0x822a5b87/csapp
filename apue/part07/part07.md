# 进程环境

## 7.2 main 函数

1. c 总从 main 函数开始执行
2. 当内核执行C程序时，在调用main前先调用一个特殊的启动例程。可执行程序文件将此启动例程指定为程序的起始地址——这是由连接器设置的，而连接器则由C编译器调用。启动例程从内核取得命令行参数和环境变量值，然后为按上述方式调用main函数做好安排。

## 7.3 进程终止

1. 有五种正常退出方式，从main返回，调用exit，调用 `_exit` 或者 `_Exit`，最后一个线程从启动例程返回，从最后一个线程调用 pthread_exit
2. 有三种异常退出方式：调用 abort，接收到一个信号，最后一个线程对取消请求作出响应
3. 上节提到的启动例程类似于 `exit(main(argc, argv))`

## 7.5 环境表

1. 每个程序都接收一张环境表；
2. **全局变量 environ** 则包含了该指针数组的地址：`extern char **environ`，按照惯例环境由 `name=value` 组成

## 7.6 C 程序的内存布局

1. [Memory Layout of C Programs](https://www.geeksforgeeks.org/memory-layout-of-c-program/)
2. .`text`: contains executable instructions, often read-only
3. `initialzed data(.data)`: contains the global variables and static variables that are initialized by the programmer; not read-only
4. `Uninitialized Data Segment(.bss)`: Data in this segment is initialized by the kernel to arithmetic 0 before the program starts executing;uninitialized data starts at the end of the data segment and **contains all global variables and static variables that are initialized to zero or do not have explicit initialization in source code.**
5. `stack`: 自动变量以及每次函数调用时所需保存的信息都存放在此段中
6. `heap`: 自动变量以及每次函数调用时所需保存的信息都存放在此段中

## 7.7 共享库

1. 共享库可以在某个所有进程都可以引用的存储区域保存某个可执行函数的副本，并在第一次调用的时候进行动态链接。

## 7.8 存储空间分配

1. malloc()；分配初始值不定
2. calloc()；分配指定长度并初始化为 0
3. realloc()；增加或减少分配区长度，增加时有可能会移动原来分配的内存区域，新增区域的值不确定

```c
void *malloc(size_t size);
void *calloc(size_t nobj, size_t size);
void *realloc(void *ptr, size_t newsize);

void free(void *ptr);
```

1. 返回指针或 NULL
2. 分配的指针是内存对齐的
3. **realloc(ptr, newsize) 有可能会修改 ptr 的位置，所以对于一个我们调用 realloc 的内存区域，不应该有第二个指针指向这片内存**
4. 大多数 malloc 的实现比所要求的稍大一些，额外的空间用来记录管理信息 -- 分配块的长度、指向下一个分配块的指针等

## 7.9 环境变量

```c
char *getenv(const char *name);
```

1. 返回与name关联的环境变量的指针或者 NULL

---

```c
int putenv(char *str);
// 返回0 或 非0

int setenv(const char *name, const char *value, int rewrite);
int unsetenv(const char *name);
// 返回 0 或 -1
```

1. 这些函数不是所有的操作系统都提供
2. putenv 和 setenv 有区别，setenv 的实现必须为 set 的环境变量分配空间；而 putenv 则不必，所以 **putenv 不能使用栈上的存储区域**
3. 简单来讲，<2> 就是 putenv 简单的把指向 `char *` 的指针添加到了 environ 中。而 setenv 则为每个环境变量新分配了存储空间。

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    char *hp = getenv("SHELL");
    printf("%s\n", hp);
    // /bin/zsh

    if (setenv("SHELL", "/bin/bash", 0) != 0)
        err_sys("setenv SHELL failed");
    hp = getenv("SHELL");
    printf("%s\n", hp);
    // /bin/zsh

    if (setenv("SHELL", "/bin/bash", 1) != 0)
        err_sys("setenv SHELL failed");
    hp = getenv("SHELL");
    printf("%s\n", hp);
    // /bin/bash

    const char *ep  = "Test_env=test_env_value";
    const char *ep2 = "Test_env=another_test_env_value";
    char       mutable_env[MAXLINE];
    strcpy(mutable_env, ep);
    if (putenv(mutable_env) != 0)
        err_sys("failed putenv");

    hp = getenv("Test_env");
    printf("Test_env = %s\n", hp);
    // Test_env = test_env_value
    printf("edit Test_env\n");
    strcpy(mutable_env, ep2);
    hp = getenv("Test_env");
    printf("Test_env = %s\n", hp);
    // Test_env = another_test_env_value

    const char *ep3 = "setenv";
    const char *ep4 = "another setenv";
    strcpy(mutable_env, ep3);
    setenv("Another_test_env", mutable_env, 1);
    hp = getenv("Another_test_env");
    printf("Another_test_env = %s\n", hp);
    // Another_test_env = setenv
    strcpy(mutable_env, ep4);
    hp = getenv("Another_test_env");
    printf("Another_test_env = %s\n", hp);
    // Another_test_env = setenv
}
```

## 7.10 setjmp 和 longjmp

```c
int setjmp(jmp_buf env);
	// 直接调用返回 0，从 longjmp 返回则为非 0

void longjmp(jmp_buf env, int val);
```

1. goto 语句不能跨越函数；
2. 当函数的调用栈非常深的时候，我们就需要使用非局部 goto -- setjmp 和 longjmp 函数
3. **当 longjmp 返回时，大多数实现并不会回滚局部变量和寄存器变量值**。局部变量和寄存器的值是 `未定的`

```c
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
```

不进行编译优化

```bash
cc ../apue.c longjmp.c
#in f1():
#global value = 95, auto val = 96, regival = 97 volaval = 98, statval = 99
#after longjmp:
#global value = 95, auto val = 96, regival = 97 volaval = 98, statval = 99
```


```bash
cc -O ../apue.c longjmp.c
#in f1():
#global value = 95, auto val = 96, regival = 97 volaval = 98, statval = 99
#after longjmp:
#global value = 95, auto val = 2, regival = 3 volaval = 98, statval = 99
```

### 自动变量的潜在问题

1. **在自动变量的函数已经返回后，不能再引用这些自动变量**。例如，我们在一个函数里返回一个指向自动变量的指针，这个指针指向的数据是未定义的

## 7.11 getrlimit, setrlimit

```c
int getrlimit(int resource, struct rlimit *rlptr);
int setrlimit(int resource, const struct rlimit *rlptr);

struct rlimit
{
	rlim_t rlim_cur;			// soft limit : current limit
	rlim_t rlim_max;			// hard limit : maximum value for rlim_cur
};
```

1. 返回0或非0
2. 每个进程都有资源限制，可以通过这两个函数来更改
3. 任何一个进程都可以修改 soft limit，但是 soft limit 必须小于 hard limit
4. 任何一个进程都可以减少 hard limit，但是 hard limit 必须大于 soft limit
5. 只有 root 可以增加 hard limit
6. 可以通过 `RLIM_INFINITY`

```c
#include "../apue.h"
#include <sys/resource.h>

// When you put a # before an argument in a preprocessor macro,
// the preprocessor turns that argument into a character array.
#define	doit(name)	pr_limits(#name, name)

static void	pr_limits(char *, int);

int
main(void)
{
#ifdef	RLIMIT_AS
    doit(RLIMIT_AS);
#endif

    doit(RLIMIT_CORE);
    doit(RLIMIT_CPU);
    doit(RLIMIT_DATA);
    doit(RLIMIT_FSIZE);

#ifdef	RLIMIT_MEMLOCK
    doit(RLIMIT_MEMLOCK);
#endif

#ifdef RLIMIT_MSGQUEUE
    doit(RLIMIT_MSGQUEUE);
#endif

#ifdef RLIMIT_NICE
    doit(RLIMIT_NICE);
#endif

    doit(RLIMIT_NOFILE);

#ifdef	RLIMIT_NPROC
    doit(RLIMIT_NPROC);
#endif

#ifdef RLIMIT_NPTS
    doit(RLIMIT_NPTS);
#endif

#ifdef	RLIMIT_RSS
    doit(RLIMIT_RSS);
#endif

#ifdef	RLIMIT_SBSIZE
    doit(RLIMIT_SBSIZE);
#endif

#ifdef RLIMIT_SIGPENDING
    doit(RLIMIT_SIGPENDING);
#endif

    doit(RLIMIT_STACK);

#ifdef RLIMIT_SWAP
    doit(RLIMIT_SWAP);
#endif

#ifdef	RLIMIT_VMEM
    doit(RLIMIT_VMEM);
#endif

    exit(0);
}

static void
pr_limits(char *name, int resource)
{
    struct rlimit		limit;
    unsigned long long	lim;

    if (getrlimit(resource, &limit) < 0)
        err_sys("getrlimit error for %s", name);
    printf("%-14s  ", name);
    if (limit.rlim_cur == RLIM_INFINITY) {
        printf("(infinite)  ");
    } else {
        lim = limit.rlim_cur;
        printf("%10lld  ", lim);
    }
    if (limit.rlim_max == RLIM_INFINITY) {
        printf("(infinite)");
    } else {
        lim = limit.rlim_max;
        printf("%10lld", lim);
    }
    putchar((int)'\n');
}
```

## 习题

### 7.1

>在 Intel x86 系统上，使用 Linux ，如果执行一个输出 “hello, world” 的程序但不调用 exit 或 return ，则程序的返回代码为 13 （用 shell 检查），解释其原因。

因为 linux 会记录程序函数调用的返回值，如果我们的 main 函数没有返回的话，那么记录的也就是 printf 的返回值，这个值是 13.

```c
#include "../apue.h"

int f(int ret)
{
    return ret;
}

int main(int argc, char **argv)
{
    f(atoi(argv[1]));
}
```

### 7.2

>图 7-3 中的 printf 函数的结果何时才被真正输出。

标准输出是行缓冲，所以当到 '\n' 时就刷新缓冲区并立即输出了

### 7.3

>是否有方法不适用（a）参数传递、（b）全局变量这两种方法，将 main 中的参数 argc 和 argv 传递给它所调用的其他函数？

可以使用环境变量

### 7.4

>在有些 UNIX 系统实现中执行程序时访问不到其数据段的 0 单元，这是一种有意的安排，为什么？

数据段的 0 单元是空指针

### 7.5

>用 C 语言的 typedef 为终止处理程序定义了一个新的数据类型 Exitfunc ，使用该类型修改 atexit 的原型。

将 Exitfunc 定义成了一个函数指针，也可以将其定义为一个函数。并且将新的原型定义为 `int atexit(Exitfunc *func);`

```c
#include "../apue.h"
#include <stdlib.h>

typedef void (*Exitfunc)(void);

void my_atexit(Exitfunc);

void my_exit(void);

int main(int argc, char **argv)
{
    my_atexit(my_exit);
    atexit(my_exit);
}

void my_atexit(Exitfunc exitfunc)
{
    exitfunc();
}

void my_exit(void)
{
    printf("hello world from my_exit!\n");
}

```

### 7.6

>如果用 calloc 分配一个 long 型的数组，数组的初始值是否为 0 ？如果用 calloc 分配一个指针数组，数组的初始值是否为空指针？

calloc 会将分配的内存中全部设置为 0，所以 long 肯定为 0。在 c 语言中，将 0 转换为 (void *) 表示一个空指针。

**The C standard defines that 0 cast to the type void * is both a null pointer and a null pointer constant.**

[what is the difference between null and 0](https://stackoverflow.com/questions/1296843/what-is-the-difference-between-null-0-and-0)

## 7.7

>`cc /usr/bin/cc` 为什么没有显示堆和栈的大小

堆和栈是动态分配的

## 7.8

>为什么 7.7 节中两个文件的大小（879443 和 8378）不等于它们各自文本和数据大小的和？

可执行文件 a.out 包含了用于调试 core 文件的符号表信息。用 strip 命令可以删除这些信息，对两个 a.out 文件执行这条命令，它们的大小减为 798760 和 6200 字节。

## 7.9

>为什么 7.7 节中对于一个简单的程序，使用共享库以后其可执行文件的大小变化如此巨大？

printf 包含在标准I/O库中，而这个库包含了大量的函数如 printf,sprintf,dprintf,fprintf 等

## 7.10

>下面的程序是否正确

```c
#include "../apue.h"

int f1(int val)
{
    int num  = 0;
    int *ptr = &num;
    if (val == 0)
    {
        int val;
        val = 5;
        ptr = &val;
    }
    return (*ptr + 1);
}
```

不正确，在 c 中，`{}` 代表一个块级作用域，所以我们的 `ptr = &val` 实际上引用了一个自动变量。当我们从 `{}` 中退出的时候再使用 `*ptr` 得到的值是未定义的。
