# UNIX 基础知识

## 1.4 文件和目录

```c
#include "stdio.h"
#include "dirent.h"
#include "../../apue.h"

int main(int argc, char **argv)
{
    DIR           *dp;
    struct dirent *dirp;

    if (argc != 2)
    {
        err_quit("usage: ls directory_name");
    }

    if ((dp = opendir(argv[1])) == NULL)
    {
        err_quit("can't open file: ");
        err_quit(argv[1]);
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        printf("%s\n", dirp->d_name);
    }

    return 0;
}
```

## 1.5 输入和输出

### 1. 文件描述符

1. 文件描述符表示一个 **特定进程** 正在访问的文件
2. 当文件 `打开` 一个文件或者 `创建` 一个新文件时，它返回一个文件描述符

### 2. 不带缓冲的 I/O

1. `open` , `read`, `write` 等提供了不带缓冲区的 I/O
2. `出错时大多数系统函数都返回 -1`
3. 下面的程序可以读取标准输出的输入并写入到标准输出，但是如果我们通过 `./a.out < file0 > file1` 我们就可以将 file0 的数据写入到 file1 中

```c
#include "../../apue.h"

#define BUFFSIZE 4096

int main(int argc, char **argv)
{
    int  n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, n) != n)
        {
            err_sys("write error");
        }
    }

    if (n < 0)
    {
        err_sys("reade error!");
    }
}
```

### 标准 I/O

1. 标准 I/O 相对于系统 I/O 增加了缓冲区
2. 标准 I/O 包括 `printf`, `fgets` 等

```c
#include "../../apue.h"

int main(int argc, char **argv)
{
    int c;

    while ((c = getc(stdin)) != EOF)
    {
        if (putc(c, stdout) == EOF)
        {
            err_sys("output error");
        }
    }

    if (ferror(stdin))
    {
        err_sys("input error");
    }

    exit(0);
}
```

## 1.6 程序和进程

1. 程序是磁盘上的 **可执行文件**，进程是程序的一个实例；
2. getpid() 返回一个 pid_t 数据类型， **仅仅知道的标准是它能保存在一个长整型中**。虽然大部分可以用整型表示，但是使用长整型可以提高移植性
3. 进程共享 **命名空间，文件描述符，栈以及进程相关的属性**


```c
#include "../../apue.h"

int main(int argc, char **argv)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        if(buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = 0;
        }

        if((pid = fork()) < 0)
        {
            err_sys("fork_error");
        }
        else if(pid == 0)
        {
            execlp(buf, buf, (char *) 0);
            err_ret("couldn't execute %", buf);
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0)
        {
            err_sys("wait pid error");
        }

        printf("%%");
    }

    exit(0);
}
```

## 1.7 出错处理

1. 当系统函数出错时，一般会返回 -1，部分返回指针的系统函数会返回 NULL
2. `errno` 是一个可修改的整形左值， **每个线程都有属于它自己的局部 errno**
3. errno 在 errno.h 下定义
4. errno 有两条规则：
	4.1 如果没有出错，其值不会被清除。所以对于一个线程在出错之后必须手动去清除 errno
	4.2 任何系统函数不会将 errno 设置为 0


```c
#include <fcntl.h>
#include "../../apue.h"

int main(int argc, char **argv)
{
    int fd = open("non_exit_file", O_RDONLY);

    perror("open non_exit_file");
    fd = open("errno.c", O_RDONLY);

    printf("fd = %d\n", fd);
    perror("open errno.c");
    // open non_exit_file: No such file or directory
    // fd = 3
    // open errno.c: No such file or directory
}
```

## 1.8 用户标识

```c
#include "../../apue.h"

int main(void)
{
	printf("uid = %d, gid = %d\n", getuid(), getgid());

	return 0;
}
```

## 1.9 信号

1. **信号** 用于通知进程发生了某种情况
2. 收到信号，我们可以选择几种处理方式：
	2.1 忽略：不推荐，因为行为未定义
	2.2 默认：大部分异常会导致进程直接退出
	2.3 捕捉：通过 signal() 函数可以捕捉信号并确定自己的处理方式

```c
#include <errno.h>
#include "../../apue.h"

static void sig_int(int);

int main(int argc, char **argv)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if(buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if ((pid = fork()) < 0)
        {
            perror("fork");
            strerror(errno);
        }
        else if (pid == 0)
        {
            execlp(buf, buf, (char *) 0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        printf("%% ");
    }

    exit(0);
}

void sig_int(int sig)
{
    printf("interrupt!\n%%");
}

```

## 1.10 时间值

1. 日历时间（UTC）存在系统基本数据类型 `time_t` 中
2. 进程时间，也被称之为 CPU 时间，存在 `clock_t` 中
3. unix系统为进程维护了三个时间：时钟时间，用户CPU时间，系统CPU时间。分别表示系统占用CPU时间片的时间，用户态的CPU时间，内核态的CPU时间

## 1.11 系统调用和库函数

1. 所有的操作系统都提供了一些 entry，程序可以通过这些 entry 向内核请求服务
2. unix 通过为每个系统调用提供一个 C语言同名函数来暴露 entry，在实际执行时系统会调用不同的内核调用
3. 库函数可以替换，而系统调用通常是不能被替换的。例如，可以修改 malloc 来定制内存分配策略，但是 sbrk 则是系统调用无法被替换
4. 系统调用通常是一种最小接口，而库函数则提供比较复杂的功能。
