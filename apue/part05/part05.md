# 标准 I/O 

## 5.1

1. 标准I/O库处理很多细节，如缓冲区分配、以优化的块长度执行I/O等。这些处理使用户不必担心如何选择使用正确的块长度

## 5.2 流和 FILE 对象

```c
#include <stdio.h>
#include <wchar.h>

int fwide(FILE *fp, int mode);
```

1. 流是面向宽字符的，返回整数；面向字节定向的返回负数；未定向返回 0
2. mode < 0 设置流 面向字节；mode > 0，设置流面向宽字符；mode == 0 不设置流但是返回流面向的值
3. **注意，fwide 并不修改已定向的流。并且 fwide 无出错返回。我们需要通过调用 fwide 之前的 errno 来检查 fwide 的调用错误**

## 5.3 stdin,stdout,stderr

1. STDIN_FILENO,STDOUT_FILENO,STDERR_FILENO

## 5.4 缓冲

```c
#include <stdio.h>

void setbuf(FILE *restrict fp, char *restrict buf);
int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);
```

1. 调用可以更改缓冲类型：返回0或者非0
2. setbuf 简单的设置或者关闭缓冲（通过给 buf 传递 NULL 或者 BUFSIZE 大小的缓冲区指针）
3. setvbuf 提供了更加精确的控制，例如指定全缓冲，行缓冲。并且可以指定缓冲区的大小。

```c
#include <stdio.h>

int fflush(FILE *fp);
```

1. 使得所有的未写数据都被传送到内核：返回 0 或者 EOF

## 5.5 打开流

```c
FILE *fopen(const char *restrict pathname, const char *restrict type);
FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp);
FILE *fdopen(int fd, const char *type);
```

1. 打开一个标准 I/O 流：返回文件指针或者 NULL
2. type 参数指定 I/O 流的读写方式，例如 `rb`, `wb`。字符 `b` 作为 type 的一部分可以区分文本文件和二进制文件
3. fdopen 由于已经打开，所以 fdopen 是否阶段文件取决于 O_TRUNC 标志

```c
int fclose(FILE *fp);
```

1. 刷新缓冲区后关闭这个流，返回0或者EOF

## 5.6 读写写流

1. 单字符 I/O
2. 行 I/O
3. 直接 I/O（也叫二进制 I/O 等）

### 单字符 I/O

```c
int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);
```

1. 读取一个字符并返回：返回下一个字符或者EOF
2. getc 可以被实现为宏，而另外两个必须是函数

---

>上面三个函数的错误返回和到文件结尾都返回 EOF，需要通过下面的函数来确定异常情况

```c
int ferror(FILE *fp);
int feor(FILE *fp);

void clearerr(FILE *fp);
```

1. 条件为真则返回1，否则返回0

>从流中读取数据之后，可以调用 ungetc 将字符写会流中

```c
int ungetc(int c, FILE *fp);
```

1. 返回 c 或者 EOF
2. ungetc 只是把数据写回了缓冲区

### 输出函数

```c
int putc(int c, FILE *fp);
int fputc(int c, FILE *fp);
int putchar(int c);
```

1. 返回 c 或者 EOF
2. 其他特性与输入函数一样

## 5.7 行 I/O

```c
char *fgets(char *restrict buf, int n, FILE *restrict fp);
char *gets(char *buf);
```

1. 读取一行写入 buf：返回 buf 或者 NULL
2. gets 不推荐使用，因为可能造成缓冲区溢出

```c
int fputs(const char *restrict str, FILE *restrict fp);
int puts(const char *str);
```

1. 将一行数据写入到指定的流：返回非负值或者 EOF
2. puts 虽然安全但是不推荐使用，因为 puts 会多输出一个换行符

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    char buf[BUFSIZ];
    while(fgets(buf, BUFSIZ, stdin))
    {
        fputs(buf, stdout);
        printf("echo: [%s]", buf);
        // hello
        // hello
        // echo: [hello\n]
    }
}
```

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    char buf[BUFSIZ];
    while(fgets(buf, BUFSIZ, stdin))
    {
        puts(buf);
        printf("echo: [%s]", buf);
        // hello
        // hello
        //
        // echo: [hello
        // ]
    }
}
```

## 5.8 标准 I/O 的效率

```C
#include "../apue.h"

int main(int argc, char **argv)
{
    int c;
    while((c = getc(stdin)) != EOF)
    {
        if (putc(c, stdout) == EOF)
        {
            err_sys("output error");
        }
    }

    if (ferror(stdin))
        err_sys("input error");

    exit(0);
}
```

## 5.9 二进制 I/O

>我们有时候会希望一次读完一个 struct，所以提供了 fread 和 fwrite 函数

```c
size_t fread(void *restrict ptr, size_t size, size_t nitem, FILE *restrict fp);
size_t fwrite(void *restrict ptr, size_t size, size_t nitem, FILE *restrict fp);
```

1. 读/写二进制对象，返回读/写的对象数
2. 对于读，读到的数据可能少于 nitems，需要通过 ferror 或者 feof 判断。对于写，少于 nitems 则出错
3.** `fread` 和 `fwrite` 的最大问题是，他们只能读/写一个系统的数据。现在可以用 protobuf 之类的序列化协议来处理**

>读取 2~5 个元素

```c
float data[10];
if (fwrite(&data[2], sizeof(float), 4, fp) != 4)
{
	err_sys("fwrite error");
}
```

>读/写一个结构体

```c
struct
{
	short count;
	long  total;
	char  name[NAMESIZE];
} item;

if (fwrite(&item, sizeof(item), 1, fp) != 1)
{
	err_sys("fwrite error");
}
```

## 5.10 定位流

1. ftell, fseek，使用 long 存放在长整型中
2. ftello，fseeko 使用 off_t 代替
3. fgetpos，fsetpos 使用 fpos_t 代替。如果需要移植到非 unix 系统上，应当使用 fgetpos 和 fsetpos

### ftell, fseek

```c
long ftell(FILE *fp);
int fseek(FILE *fp, long offset, int whence);

void rewind(FILE *fp);
```

1. 对于二进制文件，从0开始，以字节为单位偏移
2. 对于文本文件，whence 只能使用 SEEK_SET，并且 offset 只能是0或者 ftell 的返回值，因为非UNIX系统中可能以不同的格式存放文本。

### ftello, fseeko

ftello，fseeko 除了偏移量用 off_t 表示之外，其余与 ftell，fseek 相同

### fgetpos, fsetpos

```c
int fgetpos(FILE *restrict fp, fpos_t *restrict pos);
int fsetpos(FILE *restrict fp, const fpos_t *pos);
```

1. 返回 0 或者 非0

## 5.11 格式化 I/O

### 格式化输入

```c
int printf(const char *restrict format, ...);
int fprintf(FILE *restrict fp, const char *restrict format, ...);
int dprintf(int fd, const char *restrict format, ...);

int sprintf(char *restrict buf, const char *restrict format, ...);

int snprintf(char *restrict buf, size_t n, const char *restrict format, ...);
```

1. 前面三个函数返回输出字符数或者负值，第四个函数返回存入数组的字符数或者负值，最后一个函数返回要存入数组的字符数或者负值
2. f -> file, d -> fd, s -> str
3. sprintf 会在缓冲区的结尾增加一个 null，但是该字符不包含在返回值中

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    char buf[12];
    size_t n;
    if ((n = sprintf(buf, "%s %s", "hello", "world")) < 0)
        err_sys("sprintf error: %d", n);

    printf("%zu: %s", n, buf);
}
```

### 格式化输出

```c
int scanf(const char *restrict format, ...);
int fscanf(FILE *restrict fp, const char *restrict format, ...);
int sscanf(const char *restrict buf, const char *restrict format, ...);
```

1. 返回赋值的输入项数或者EOF

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    const char *buf = "2020-01-01 17";

    unsigned y, m, d, h, s;

    int scann = 0;
    if ((scann = sscanf(buf, "%d-%d-%d %d:%d", &y, &m, &d, &h, &s)) != 5)
    {
        printf("scann = %d\n", scann);
        // scann = 4
    }
}
```

## 5.13 临时文件

```c
char *tmpnam(char *ptr);
FILE *tmpfile(void);
```

1. tmpfile 返回文件指针或者返回NULL
2. tmpnam 返回指向文艺路径名的指针
3. 如果 ptr 是 NULL，那么所产生的路径名将存放在一个静态区中，指向该静态区的指针作为函数值返回，后续调用 tmpnam 会覆盖这个静态区
4. tmpfile 创建临时二进制文件，在关闭文件或程序结束时删除

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    char *tp = tmpnam(NULL);
    printf("%s\n", tp);

    char *tp2 = tmpnam(name);
    printf("tp = %s, tp2 = %s, name = %s\n", tp, tp2, name);

    tp2 = tmpnam(NULL);
    printf("tp = %s, tp2 = %s, name = %s\n", tp, tp2, name);


    if ((fp = tmpfile()) == NULL)
        err_sys("tmpfile error");
    fputs("one line of output\n", fp);
    rewind(fp);
    if (fgets(line, MAXLINE, fp) == NULL)
        err_sys("fgets error");
    fputs(line, stdout);
}
```

## 5.14 内存流

>内存流就是所有的 I/O 都是通过在缓冲区与内存之间传送数据得来的。类似于 c++ 里的 stringstream

```c
FILE *fmemopen(void *restrict buf, size_t size, const car *restrict type);
```

1. fmemopen 允许我们提供缓冲区用于内存流

---

1. 对于 `"a"`，无论何时以追加方式打开内存流， **off_t 设置为缓冲区的第一个 null 字节**。如果不存在 null 字节就设置为缓冲区结尾的最后一个字节。

```c
int main(int argc, char **argv)
{
    char buf[BUFSIZ];
    memset(buf, '\0', 1);
    strcpy(buf + 1, "hello world");
    FILE *fp = fmemopen(buf, BUFSIZ, "r");
    if (fp == NULL)
        err_sys("fmemopen error");
    fputs(buf, fp);

    printf("[%s]\n", buf);
	// []
	fp = fmemopen(buf, BUFSIZ, "a");
    printf("buf = [%s]\n", buf);
	// buf = []
    if (fputs(" from APUE!", fp) == EOF)
        err_sys("fputs error");
    printf("buf = [%s]\n", buf);
	// buf = [ from APUE! ]
}
```

---

1. 对于 `"a"` 标签，在初始化完 off_t 之后，就和普通的追加一样了。每次都会设置数据到文件结尾，无论

```c
#include <stdio.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    char buf[BUFSIZ];
    strcpy(buf, "hello world");
    FILE *fp = fmemopen(buf, BUFSIZ, "r");
    if (fp == NULL)
        err_sys("fmemopen error");
    fputs(buf, fp);

    printf("[%s]\n", buf);

    char usrbuf[BUFSIZ];
    if (fgets(usrbuf, BUFSIZ, fp) == NULL)
        err_sys("fgets to usrbuf error");
    printf("[%s]\n", usrbuf);
    // []

    fseek(fp, 0, SEEK_SET);
    if (fgets(usrbuf, BUFSIZ, fp) == NULL)
        err_sys("fgets to usrbuf error");
    printf("[%s]\n", usrbuf);
    // [hello world]
    fclose(fp);

    fp = fmemopen(buf, BUFSIZ, "a");
    printf("buf = [%s]\n", buf);
    if (fputs(" from APUE!", fp) == EOF)
        err_sys("fputs error");
    printf("buf = [%s]\n", buf);
    // buf = [hello world from APUE!]
    fseek(fp, 0, SEEK_SET);
    if (fputs("hello world again!", fp) == EOF)
        err_sys("fputs error");
    printf("buf = [%s]\n", buf);
    // buf = [hello world from APUE!hello world again!]
    fseek(fp, 0, SEEK_SET);
    memset(buf, 0, BUFSIZ);
    if (fputs("hello world again!", fp) == EOF)
        err_sys("fputs error");
    printf("buf = [%s]\n", buf);
    for (int i = 0; i < BUFSIZ; ++i)
    {
        printf("%c", buf[i]);
    }
    // (n NULL)hello world again!(other NULL)
}
```

```c
#include <stdio.h>
#include "../apue.h"

#define BSZ 48

int main(int argc, char **argv)
{
    FILE *fp;
    char buf[BSZ];

    memset(buf, 'a', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'X';
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
        err_sys("fmemopen failed");

    printf("initial buffer contents:%s\n", buf);
    // "w+" 打开将截断内存流
    // initial buffer contents:
    fprintf(fp, "hello world!");
    printf("before flush:%s\n", buf);
    fflush(fp);
    printf("after flush:%s\n", buf);
    printf("len of string in buf = %ld\n", (long) strlen(buf));

    memset(buf, 'b', BSZ-2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'x';
    fprintf(fp, "hello world!");
    printf("before fseek: %s\n", buf);
    fseek(fp, 0, SEEK_SET);
    printf("after  fseek: %s\n", buf);
    printf("len of string in buf = %ld\n", (long) strlen(buf));

    memset(buf, 'c', BSZ-2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'x';
    fprintf(fp, "hello, world");
    fclose(fp);
    printf("after fclose: [%s]\n", buf);
    printf("len of string in buf = %ld\n", (long) strlen(buf));
}
```

---

### 其他创建内存流的函数

```c
FILE *open_memstream(char *bufp, size_t *sizep);
FILE *open_wmemstream(wchar_t **bufp, size_t *sizep)
```

1. 返回流指针或者 NULL

## 标准 I/O 的替代品

1. fgets 和 fputs 需要复制两次数据：一次是内核和标准I/O的缓冲区，第二次是在标准I/O缓冲区和用户程序的行缓冲区
2. 快速I/O(fio)的给出了一个方法：读一行的函数返回指向该行的指针，而不是将其复制到一个缓冲区

## 习题

### 5.1

>用 setvbuf 实现 setbuf <br />
>[cplusplus/setbuf](http://www.cplusplus.com/reference/cstdio/setbuf/)
>[cppreference/setbuf](https://en.cppreference.com/w/cpp/io/c/setbuf)

1. A call to this function is equivalent to calling setvbuf with `_IOFBF` as mode and BUFSIZ as size (when buffer is not a null pointer), or equivalent to calling it with `_IONBF` as mode (when it is a null pointer).

```c
void my_setbuf(FILE * __restrict fp, char * __restrict buf)
{
    if (buf == NULL)
        setvbuf(fp, NULL, _IONBF, 0);
    else
        setvbuf(fp, buf, _IOFBF, BUFSIZ);
}
```

## 5.2

>图 5-5 中的程序利用每次一行 I/O （fgets 和 fputs 函数）复制文件。若将程序中的 MAXLINE 改为 4 ，当复制的行超过该最大值时会出现什么情况？请对此进行解释

```c
#include "../apue.h"

#ifndef MAXLINE0
#define MAXLINE0 4
#endif

int main(int argc, char **argv)
{
    char buf[MAXLINE0];
    while(fgets(buf, MAXLINE0, stdin) != NULL)
    {
        fputs(buf, stdout);
        printf("echo: [%s]", buf);
		// hello
		// helecho: [hel]lo
		// echo: [lo
		// ]
    }
}
```

1. fgets 首先读取 MAXLINE0 - 1 个字符到缓冲区，因为缓冲区需要以 '\0' 结尾；
2. fputs 调用后，会刷新缓冲区，随后缓冲区的可用长度又变为 MAXLINE0

## 5.3 

>printf 返回 0 值表示什么？

代表空白输出

## 5.4

>下面的代码在一些机器上运行正确，而在另外一些机器运行时出错，解释原因所在

```c
#include <stdio.h>

int main() {
    char c;
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
}
```

1. 根据 `c++ primer` ：int、short、long 和 long long 都是带符号的；字符却分为三种：signed char, unsigned char。而 char 具体体现为那种由编译器决定
2. getchar() 返回的是一个 int，如果编译器是无符号，而 EOF 又被定义为负数的话，那么这个函数将永远无法正常返回。

### 5.5

>对标准 I/O 流如何使用 fsync 函数（见 3.13 节）？

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    FILE *fp = stdout;
    int  fd  = fileno(fp);
    printf("stdin fd = %d\n", fd);
}
```

1. [Difference between fflush and fsync](https://stackoverflow.com/questions/2340610/difference-between-fflush-and-fsync)
2. fflush 是标准I/O库中的函数，我们调用 fflush 将数据从标准I/O的缓冲区传送到内核；
3. fsync 等是作用域 fd，我们调用 fsync 将数据从内核写到磁盘
