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
