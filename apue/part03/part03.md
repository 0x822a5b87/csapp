# 文件I/O

## 3.1 引言

1. 大多数文件只需要用到 `open`, `read`, `write`, `lseek` 和 `close` 
2. 上面的这些函数是不带缓冲的，每一次调用都是一次内核中的一个系统调用

## 3.2 文件描述符

1. 对于内核，所有打开的文件都通过文件描述符引用

## 3.3 函数 open 和 openat

```c
#include <fcntl.h>
int open(const char *path, int oflag,... /* mode_t mode */);
int openat(int fd, const char *path, int oflag, ... /* mode_t mode */ );
```

1. 成功返回描述符，失败返回 -1。晋档创建新文件时我们才会去创建这个函数
2. 常用的 oflag
	2.1 O_RDONLY
	2.2 O_WRONLY
	2.3 O_RDWR
	2.4 O_APPEND
	2.5 O_EXCL 如果同时指定了 O_CREAT 而文件已经存在则出错
	2.6 O_CLOEXEC **It marks the file descriptor so that it will be close()d automatically when the process or any children it fork()s calls one of the exec*() family of functions.**
3. 第三个参数的 `mode`，用来 指定文件的访问权限位

>当执行一个 `fork()` 指令的时候，子进程会获得父进程的所有 fd。而当子进程执行 exec() 指令的时候，此时会用全新的程序替换子进程的正文，数据，堆和栈等。这个时候会产生 fd 泄漏。设置 O_CLOEXEC 会是的程序在执行 exec-family 的指令时自动调用 close()

## 3.4 create

```c
#include <fcntl.h>

int create(const char *path, mode_t mode);

// 等效于
open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
```

1. 返回 fd 或者 -1
2. 新版本可以直接用 open 函数

## 3.5 close

```c
#include <fcntl.h>

int close(int fd);
```

1. 返回 0 或 -1
2. 进程在终止时内核会自动关闭它打开的文件

## 3.6 函数 lseek

```c
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

1. 返回 **新的文件偏移量** 或者 -1
2. whence 参数决定了 offset 的解释
	2.1 SEEK_CUR
	2.2 SEEK_END
	2.3 SEEK_SET
3. **off_t 是带符号数据类型**
4. off_t 仅仅被记录在文件内核中

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
    {
        printf("cannot seek\n");
    }
    else
    {
        printf("seek OK\n");
    }
    return 0;
}
```

```c
#include <fcntl.h>
#include "../apue.h"

off_t Lseek(int, off_t, int);

int main(int argc, char **argv)
{
    int fd = open(__FILE__, O_CREAT | O_RDONLY);
    if (fd < 0)
        return -1;

    off_t offset = Lseek(fd, 0, SEEK_CUR);
    printf("current offset = %lld\n", offset);
    offset = Lseek(fd, 0, SEEK_END);
    printf("end offset = %lld\n", offset);

    offset = Lseek(fd, -offset, SEEK_END);
    printf("start offset = %lld\n", offset);
}


off_t Lseek(int fd, off_t offset, int mode)
{
    off_t cur_off;
    if ((cur_off = lseek(fd, offset, mode)) == -1)
    {
        exit(-1);
    }
    return cur_off;
}
```

>文件允许存在空洞

```c
#include <fcntl.h>
#include "../apue.h"

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char **argv)
{
    int fd;
    if ((fd = creat("file.hoe", FILE_MODE)) < 0)
        err_sys("creat error");
    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");

    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");

    exit(0);
}

```

## 3.7 函数 read

```c
#include <unistd.c>

ssize_t read(int fd, void *buf, size_t nbytes);
```

1. 返回读取成功的字节数，0（到达文件结尾），-1
2. ssize_t 是一个有符号整数，因为返回值有可能小于零
3. 返回的字节数有可能小于预期的字节数 nbytes

## 3.8 函数 write

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t nbytes);
```

1. 成功则返回已写的字符串；如果出错则返回 -1.
2. 返回值通常和 nbytes 相同，否则表示出错。例如磁盘已满等其他问题。


## 3.9 I/O 的效率

```c
#include "../apue.h"

#define BUFFSIZE 20

int main(int argc, char **argv)
{
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, n) != n)
        {
            err_sys("write error");
        }
    }

    if (n < 0)
        err_sys("read error");

    exit(0);
}

```

1. 在实验中，当读取一个 516,581,760 字节的文件时。采用 BUFFSIZE == 1 和 BUFFSIZE == 32 时用户CPU，系统CPU，时钟时间都大幅度降低了；
2. BUFFSIZE == 32 和 BUFFSIZE == 524288，用户CPU和系统CPU都下降了，但是时钟时间却差不多；

## 3.10 文件共享

1. 每个进程在进程表中包含一个文件描述符表，表中的每个表项包含了：
	1.1 文件描述符
	1.2 指向文件表中的某一项的指针
2. 文件表：
	2.1 文件状态标志
	2.2 文件偏移量
	2.3 指向 v-node 的指针
3. v-node 表：
	3.1 文件类型
	3.2 对此文件进行各种操作的函数的指针
	3.3 其他信息

---

>如果用 O_APPEND 打开的文件， 每次 write 前都会将文件偏移量设置为 i 节点中文件的长度

```c
#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int fd = open(__FILE__, O_WRONLY | O_CREAT | O_APPEND);

    char *buf = "\n//append test\n";
    off_t offset = lseek(fd, 0, SEEK_CUR);
    printf("append offset = %lld\n", offset);
    write(fd, buf, strlen(buf));
    offset = lseek(fd, 0, SEEK_SET);
    printf("after seek append offset = %lld\n", offset);
    write(fd, buf, strlen(buf));
}
//append test

//append test

```

---

### 文件描述符，文件表，v-node 表

1. 文件描述符是每个进程独享的，调用一次 open 就会产生一个文件描述符
2. 文件描述符不直接指向 v-node 表，是因为文件的部分属性是每个打开文件的实例独享的：例如 offset，oflag 等。而有的属性是共享的，例如文件大小，最后修改时间。


## 3.11 原子操作

```c
// 早期不支持 O_APPEND 的话要这么处理
if (lseek(fd,OL, 2) < 0)　　　　　　/*position to EOF*/
if (write(fd, buf, 100) != 100)　　/*and write*/
err_sys("lseek error");
err_sys("write error");
```

1. 上面的例子中可能会存在并发问题，因为 lseek 和 write 不是原子操作
2. O_APPEND 可以解决是因为，内核每次在写操作之前，都将进程的偏移量设置到该文件的尾端。

#### 创建文件的原子操作

```c
// 这个操作是原子的
int fd = open(path, O_CREAT | O_EXCL);
```

## 3.12 函数 dup 和 dup2

```c
#include <unistd.h>

int dup(int fd);
int dup2(int fd, int fd2);
```

1. 返回 **新的文件描述符** 或者 -1
2. dup 将文件描述符 fd 指向一个新打开的描述符指向的文件表项，dup2 将 fd2 指向 fd 指向的文件表项。 **也就是说 fd 和 fd2 指向同一个文件表项**
3. dup 和 dup2 是将文件描述符 fd 指向一个另外一个文件表项，而不是修改 fd。所以它也会改变文件的 oflag，和偏移量

```c
#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    char buf[MAXLINE];
    int fd  = open(__FILE__, O_RDONLY);
	int nfd = dup2(STDOUT_FILENO, fd);
    // fd = [3], nfd = [3]
    // write [20] char!
    sprintf(buf, "fd = [%d], nfd = [%d]\n", fd, nfd);
    if (write(nfd, buf, strlen(buf)) != strlen(buf))
    {
        printf("write error!");
    }
    else
    {
        printf("write [%lu] char!\n", strlen(buf));
    }
}
```

## 3.13 函数 sync，fsync  和 fdatasync

```c
#include <unistd.h>

int fsync(int fd);
int fdatasync(int fd);

void sync(void);
```

1. 成功返回 0，失败返回 -1
2. **sync 只是将所有修改过的块缓冲区写入队列，并不实际的等磁盘实际写操作完成**
3. fsync 刷新 fd 并且等待磁盘操作结束
4. fdatasync 刷新 fd 并且等待磁盘操作结束，但是只刷新数据部分

## 3.14 函数 fcntl

1. fcntl 可以用来赋值/获取/修改文件的 fd，oflags 等。
2. 虽然 open 方法可以指定文件的 fd 和 oflags 等属性，但是需要知道文件的路径名。而很多时候，例如在使用管道的时候，我们只知道他的 fd。这个时候我们就需要通过其 fcntl 里控制了。
3. fcntl 返回值 > 0 并不代表一定生效：例如 fcntl 通过 F_SETFL 指定 O_SYNC 时，有可能会不生效。

```c
#include <fcntl.h>

int fcntl(int fd, int cmd, ...);
```

---

```c
#include "../apue.h"
#include "fcntl.h"

int main(int argc, char **argv)
{
    int val;

    if (argc != 2)
        err_quit("usage: a.out <descriptor>");

    if ((val = fcntl(atoi(argv[1]), F_GETFL)) < 0)
        err_sys("fcntl error for fd %d", atoi(argv[1]));


    // 因为历史原因，RDONLY, WRONLY 这些标志位不是互斥的
    switch (val & O_ACCMODE)
    {
        case O_RDONLY:
            printf("read only");
            break;
        case O_WRONLY:
            printf("write only");
            break;
        case O_RDWR:
            printf("read write");
            break;
        default:
            err_dump("unknown access mode");
    }

    if (val & O_APPEND)
    {
        printf("append");
    }
    else if (val & O_NONBLOCK)
    {
        printf("non block");
    }
    else if (val & O_SYNC)
    {
        printf("sync");
    }

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (val & O_FSYNC)
        printf(", synchronous writes");
#endif

    putchar('\n');
    exit(0);
}
```

#### fcntl 的一些应用

```c
#include <fcntl.h>
#include "../apue.h"

void set_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        err_sys("fcntl F_GETFL error");

    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0)
        err_sys("fcntl F_SETFL error");
}

void clr_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        err_sys("fcntl F_GETFL error");

    val &= ~flags;

    if (fcntl(fd, F_SETFL, val) < 0)
        err_sys("fcntl F_SETFL error");
}

```

## 3.15 函数 ioctl 

```c
#include <unistd.h>
#include <sys/ioctl.h>

int ioctl(int fd, int request, ...);
```

1. 出错返回 -1，成功返回其他值

## 3.16 /dev/fd

1. 较新的系统提供 `/dev/fd` 的目录，目录项是 0、1、2 等文件描述符
2. `fd = open("/dev/fd/0", mode)` 等效于 `fd = dup(0)`
3. /dev/fd 主要提供给 shell 使用，它允许使用路径名作为调用参数的程序，能用处理其他路径名的相同方式处理标准输入和标准输出

## 习题

### 3.1

>read 和 write 是不带缓冲机制的吗？

所有的 I/O 操作基本都需要经过内核的缓冲区，这里说不带缓冲机制是没有用户态的缓冲机制。也就是每次一次 read 或者 write 都会执行一次系统调用

### 3.2

>实现一个 dump2 功能相同的函数

注意，这里使用了一个小技巧：那就是在我们 while 循环的过程中，每次都需要初始化一个 Node。如果我们初始化的 Node 是用于存放下一次循环的元素，那么有可能在下次 while 循环时条件不满足而退出，导致我们的这个 Node 节点未被正常的赋值。
所以，我们每次 while 循环中初始化的 Node 节点都用来存放当前需要存放的 Node 节点。这样的话有两种途径：保存一个指针指向 Node 内部的 struct Node*，或者像我们在代码中一样，链表中的第一个元素为空元素，并且使用一个 cur 来遍历。这样每次 cur 就指向了当前节点的前一个节点。在 free 的时候我们也跳过第一个空元素即可

```c
#include "../apue.h"

struct Node
{
    int         fd;
    struct Node *next;
};

void free_fd(struct Node *head)
{
    if (head == NULL)
        return;

    struct Node *cur;
    while (head->next != NULL)
    {
        close(head->next->fd);
        printf("close fd %d\n", head->next->fd);
        cur = head->next;
        free(head);
        head = cur;
    }
}

int my_dup2(int fd, int fd2)
{
    if (fd == fd2)
        return fd2;

    close(fd2);

    struct Node *head = (struct Node *) malloc(sizeof(struct Node));
    struct Node *cur  = head;
    int         tmp_fd;
    while ((tmp_fd = dup(fd)) < fd2)
    {
        if (tmp_fd == -1)
        {
            printf("error dup fd\n");
            free_fd(head);
            return fd;
        }

        printf("create fd = [%d]\n", tmp_fd);
        struct Node *tmp_node = (struct Node *) malloc(sizeof(struct Node));
        tmp_node->fd   = tmp_fd;
        tmp_node->next = NULL;
        cur->next = tmp_node;
        cur = cur->next;
    }

    free_fd(head);
    return fd2;
}

int main()
{
    int fd = my_dup2(STDOUT_FILENO, 15);
    printf("after dup : fd = [%d]\n", fd);
    write(15, "Hello World!\n", 13);
    return 0;
}
```

### 3.3

1. `int fd = dup(fd2);` 后 fd2 和 fd 指向同一个文件表项
2. open 同一个 path 会打开一个新的文件表项

### 3.5

>digit1 > &digit2 表示将 digit1 重定向到 digit2，描述一下<br/>
>./a.out > outfile 2>&1	<br />
>./a.out 2>&1 > outfile <br />
>的区别

1. `2>&1` 是将标准错误重定向到标准输出。相当于 dup2(1, 2);
2. `./a.out > outfile 2>&1` 先将标准输出重定向到 outfile，随后将标准错误重定向只标准输出。因为 dup2 是修改 fd 指向的文件表项，所以相当于最后将 2 和 1 都指向了 outfile
3. `./a.out 2>&1 > outfile` 将标准错误指向标准输出指向的文件表，随后将标准输出指向 outfile，所以最后相当于将 2 指向 1 原来的文件，1 指向了 outfile

## 3.6

>如果使用 O_APPEND 读写打开文件，是否能使用 lseek 在任意位置开始读？能否用 lseek 更新文件任意部分的数据

可以任意读，但不能任意写。根据 3.11 的说明：**O_APPEND 标志使得内核在每次写操作之前，都将进程的偏移量设置到该文件的尾端，于是就不需要在写之前调用 lseek**
