# 文件和目录

## 4.2 stat family

```c
#include <sys/stat.h>

int stat(const char *restrict pathname, struct stat *restrict buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *restrict pathname, struct stat *restrict buf);
int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flag);
```

1. 成功返回 0，失败返回 -1
2. stat 和 fstat 返回文件相关信息；当文件是一个符号链接时，返回符号链接的信息而不是返回符号链接指向的文件的信息；
3. fstatat 返回一个相当于当前打开目录（fd 指定）的路径名返回文件统计信息；

```c
#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int fd = open(__FILE__, O_RDONLY);

    // 注意，stat 中是不包含文件名的。因为 linux 中一个文件可以有多个文件名
    struct stat s;
    if (fstat(fd, &s) == -1)
        err_quit("failed fstat [%d]", __FILE__);

    char filePath[MAXLINE];
    if (fcntl(fd, F_GETPATH, filePath) != -1)
    {
        printf("file path = [%s]\n", filePath);
    }
}
```

## 4.3 文件类型

### 所有文件类型

1. 普通文件：二进制，linux 不处理二进制的具体内容
2. 目录文件
3. 块特殊文件：对设备带缓冲的访问，访问长度不可变
4. 字符特殊文件：对设备不带缓冲的访问，访问长度可变。
5. FIFO：进程通信用
6. socket：一般用于网络通信
7. symbolic link：指向另外一个文件

>可执行文件是一个特殊的普通文件，需要有固定的格式 unix 才有办法理解。例如，执行指令时需要知道指令的长度；需要知道链接的具体情况。在 linux 上是 elf 格式。

### 宏

1. 可以通过宏来确定文件类型，宏包含在 `sys/stat.h` 头文件下。因为是 `stat` 相关的宏，所以宏都以 `S_` 开头
2. **使用 stat 会观察不到符号链接**

```c
#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    char cwd[MAXLINE];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }

    struct stat s;
    if (stat(cwd, &s) == -1)
        err_quit("stat err");

    if (S_ISDIR(s.st_mode))
    {
        printf("%s is dir file", cwd);
    }

    return 0;
}
```

## 4.4 设置用户ID和设置组ID

### ID 类型

1. 实际uid和实际gid：标志我们究竟是谁，**当我们登陆的时候，这两个ID就已经确定了**
2. 有效uid，有效gid以及附属gid决定了我们的文件访问权限
3. 保存的uid和保存的gid在执行一个程序时包含了有效uid和有效gid的副本

---

1. `stat` 中的 st_uid 和 st_gid 指定了文件的所有者和组所有者
2. 当执行一个文件时，进程的有效uid和gid通常就是实际uid和gid。但是我们可以通过 `st_mode` 设置一个特殊的标志位，其含义是 “当执行此文件时，将进程的有效用户ID设置为文件所有者的用户ID”。例如，所有的用户都可以修改 /etc/passwd，但是只有 root 有权限修改，则个时候我们使用这个标志实现该功能。
3. 与 <2> 类似，可以通过设置 `st_mode` 的另外一位来 实现 “当执行此文件时，将有效组ID设置为文件所有者的组ID”
4. <2> 和 <3> 提到的两个标志位称之为 **设置用户ID位** 和 **设置组ID位**
5. 通过 `S_ISUID` 和 `S_ISGID` 可以测试设置用户ID位以及设置组ID位

```c
#include <fcntl.h>
#include "../apue.h"

void test(const char *path)
{
    struct stat s;
    lstat(path, &s);
    printf("%s isuid = %d, isgid = %d\n", path, S_ISUID & s.st_mode, S_ISGID & s.st_mode);
}

int main(int argc, char **argv)
{
    test(__FILE__);
    test("/etc/passwd");
}

```

## 4.5 文件访问权限

1. S_IRUSR
2. S_IRGRP
3. S_IROTH

>The "S" is for STAT, the "I" for INODE

### 权限判断

1. 如果打开一个文件，那么对于文件路径的所有目录都必须有执行权限，这也是为什么目录的执行权限被称之为 **搜索位** 的原因。例如 `vim /usr/include/stdio.h` 需要对 `/usr`，`/usr/include` 都有执行权限
2. 权限测试先测试是否为 root，root 拥有全部权限，随后如果实际uid 和文件uid 匹配则检查用户的权限。注意，如果用户权限检查失败则直接拒绝而不会继续检查组权限。如果实际uid和文件uid不匹配则检查组权限。直到检查到 OTHER

## 4.6 新文件和目录的所有权

1. 新建文件的 uid 是进程的 有效uid
2. 新建文件的 gid 是进程的 有效gid 或者所在目录的 gid

## 4.7 access 和 faccessat

```c
#include <unistd.h>

int access(const char *path, int mode);
int faccessat(int fd, const char *path, int mode, int flag);
```

1. 成功返回 0，失败返回 -1
2. flag 设置为 AT_EACCESS，访问检查用的是调用进程的有效用户ID和有效组ID而不是实际用户ID和实际组ID

```c
#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        err_quit("usage: a.out <pathname>");

    // fd == AT_FDCWD 时与 access 权限一致
    if (faccessat(AT_FDCWD, argv[1], R_OK, AT_EACCESS) < 0)
        err_ret("access error for %s", argv[1]);
    else
        printf("read access OK\n");

    if (open(argv[1], O_RDONLY) < 0)
        err_ret("open error for %s", argv[1]);
    else
        printf("open for reading OK\n");

    return 0;
}
```

## 4.8 umask

```c
#include <sys/stat.h>

mode_t umask(mode_t cmask);
```

1. 返回之前的文件的 `st_mode`
2. 调用 umask 会设置一个屏蔽值 mask，之后当我们调用 creat 方法时，会用 creat 的 cmask & msdk 得到一个新的 mask 赋给创建的文件

```c
#include <fcntl.h>
#include "../apue.h"

#define RWRWRW (S_IRWXU|S_IRWXG|S_IRWXO)

int main(int argc, char **argv)
{
    umask(0);
    if (creat("foo", RWRWRW) < 0)
        err_sys("creat error for foo");
    umask(S_IRGRP | S_IWGRP | S_IWOTH);
    if (creat("bar", RWRWRW) < 0)
        err_sys("creat error for bar");
    exit(0);
}
```

-rwx--xr-x  1 dhy  staff     0B Dec 27 18:05 bar
-rwxrwxrwx  1 dhy  staff     0B Dec 27 18:05 foo

>umask 屏蔽了用户组的读写权限和附加组的写权限

## 4.9 chmod、fchmod 和 chmodat

```c
#include <sys/stat.h>

int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);
int fchmodat(int fd, const char *pathname, mode_t mode, int flag);
```

1. 成功返回0，出错返回-1
2. fchmodat 在 pathname 为绝对路径或者 fd == AT_FDCWD 而参数为相对路径时，和 fchmod 一样
3. flag 修改 fchmodat 的行为，AT_SYMLINK_NOFOLLOW 表示不会跟随符号链接

```c
#include <fcntl.h>
#include "../apue.h"

#define RWRWRW (S_IRWXU|S_IRWXG|S_IRWXO)

int main(int argc, char **argv)
{
    struct stat s;
    int         mode = (s.st_mode & ~S_IXGRP) | S_ISGID;
    printf("mode = [%d]\n", mode);

    if (stat("foo", &s) < 0)
        err_sys("stat error for foo");
    if (chmod("foo", mode) < 0)
        err_sys("chmod error for foo");
    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
        err_sys("chmod error for bar");
}
```

-rw-r--r--   1 dhy  staff     0B Dec 27 18:05 bar
------S---   1 dhy  staff     0B Dec 27 18:05 foo

## 4.11 chown、fchown、fchownat 和 lchown

```c
#include <unistd.h>

int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int fchownat(int fd, const char *pathname, uid_t owner, gid_t group, int flag);
int lchown(const char *pathname, uid_t owner, gid_t group);
```

1. 4个函数的返回值：若成功，返回0；若出错，返回-1
2. 除了引用文件是符号链接的情况下，这四个函数的操作类似。在符号链接的情况下，lchown 和 fchownat(设置 flag 为 AT_SYMLINK_NOFOLLOW) 更改符号链接本身的所有者而不是符号链接指向的文件的所有者

## 4.12 文件长度

1. stat 的 st_size 表以字节为单位的文件的长度，st_blksize 是对文件I/O合适的块长度，st_blocks 是所分配的实际 512(不同系统不同) 字节块块数

## 4.13 文件截断

```c
#include <unistd.h>

int truncate(const char *path, off_t len);
int ftruncate(int fd, off_t len);
```

1. 返回 0 或者 -1
2. 将文件长度截断为 len

## 4.14 文件系统

[linux 文件系统详解](https://juejin.im/post/5b8ba9e26fb9a019c372e100)

1. 标准的 Linux 文件系统 Ext2 是使用「基于 inode 的文件系统」
2. 在基于 inode 的文件系统中，权限与属性放置到 inode 中，实际数据放到 data block 区块中，而且 inode 和 data block 都有编号

### inode table: 

1. 主要记录文件的属性以及该文件实际数据是放置在哪些 block 中
2. 一个文件占用一个 inode，每个 inode 有编号
3. 系统读取文件时需要先找到 inode，并分析 inode 所记录的权限与使用者是否符合，若符合才能够开始实际读取 block 的内容

### data block

1. 放置文件内容数据的地方
2. 在格式化时 block 的大小就固定了，且每个 block 都有编号，以方便 inode 的记录
3. 每个 block 内最多只能够放置一个文件的资料，但一个文件可以放在多个 block 中

### superblock

1. 记录整个文件系统相关信息的地方，记录的信息主要有：block 与 inode 的总量，未使用与已使用的 inode /block 数量等等。
2. 每个块都可能含有 superblock，但是我们也说一个文件系统应该仅有一个 superblock 而已，那是怎么回事？事实上除了第一个块内会含有 superblock 之外，后续的块不一定含有 superblock，而若含有 superblock 则该 superblock 主要是做为第一个块内 superblock 的备份，这样可以进行 superblock 的救援

### Filesystem Description

这个区段可以描述每个 block group 的开始与结束的 block 号码，以及说明每个区段 (superblock, bitmap, inodemap, data block) 分别介于哪一个 block 号码之间

### block bitmap

1. 块对照表 : 它会记录哪些 block 是空的

### inode bitmap

1. 与 block bitmap 是类似的功能，只是 block bitmap 记录的是使用与未使用的 block 号码， 至于 inode bitmap 则是记录使用与未使用的 inode 号码

## 4.15 link、linkat、unlink、unlinkat、remove

```c
#include <unistd.h>

int link(const char *existingpath, const char *newpath);
int linktat(int efd, const char *existingpath, int nfd, const char *newpath, int flag);
```

1. 返回 0 或者 -1
2. 对于 linkat 如果任意一个 fd 为 AT_FDCWD 那么从当前目录计算，如果任意一个设置为绝对路径，那么文件描述符参数被忽略
3. 由 flag 来控制指向现有符号链接还是现有符号链接所指向的文件链接

```c
#include <unistd.h>

int unlink(const char *pathname);
int unlinkat(int fd, const char *pathname, int flag);
```

1. 成功返回 0，失败返回 -1
2. 还是老一套，如果 fd == AT_FDCWD 那么指向当前工作目录的 pathname，否则指向 fd 目录下的 pathname。如果 pathname 为绝对目录则忽略 fd 参数
3. unlink 有一个特性：对于已经打开的文件，unlink 不会删除内容，当进程关闭的时候会自动的删除掉文件。
4. 基于 <3> 我们用 open 或 creat 创建一个文件，然后立马 unlink 它，那么直到程序奔溃的时候才会自动的删除掉这个文件。

### remove

1. 返回 0 或 -1
2. 对于文件，remove 功能和 unlink 相同。对于目录，remove 功能和 rmdir 相同

## 4.16 rename，renameat

```c
#include <stdio.h>

int rename(const char *oldname, const char *newname);
int renameat(int oldfd, const char *oldname, int newfd, const char *newname);
```

1. 成功返回 0，失败返回 -1
2. 当 oldname 和 newname 都设置为绝对路径时， renameat 和 rename 功能相同
3. oldname 和 newname ，如果设置为相对路径，那么按照 oldfd 或者 newfd 对应的路径名查找

## 4.17 符号链接

1. 符号链接是一个文件的间接指针。和硬链接不同，硬链接直接指向文件的 inode。
2. 符号链接有自己的 inode，并且 data block 保存了链接指向的文件的绝对地址。

## 4.18 创建和读取符号链接

```c
#include <unistd.h>

int symlink(const char *actualpath, const char *sympath);
int symlinkat(const char *actualpath, int fd, const char *sympath);
```

1. 返回0或-1
2. symlinkat 根据 fd 的相对路径链接，如果 fd == AT_FDCWD 或者 actualpath 为绝对地址则等同于 sympath

```c
#include <unistd.h>

ssize_t readlink(const char *restrict pathname, char *restrict buf, size_t bufsize);
ssize_t readlinkat(int fd, const char *restrict pathname, char *restrict buf, size_t bufsize);
```

1. 返回读取的字节数或 -1
2. 符号链接内容不以 NULL 终止

## 4.19 文件的时间

1. `st_atim` = access time, `st_mtim` = modify time, `st_ctim` = change time
2. 分别对应文件最后访问时间，最后修改时间，元数据发生变化时间。
3. mtim 是 **文件内容** 最后一次被修改时间，而 ctime 是 **文件的 i 节点** 的最后一次修改时间

## 4.20 futimens，utimensat， utimes

```c
#include <unistd.h>

int futimens(int fd, const struct timespec times[2]);
int utimensat(int fd, const char *path, struct timespec times[2], int flag);
```

1. futimens, utimensat -- set file access and modification times
2. 成功返回0，出错返回-1
3. times 第一个元素包含访问时间，第二个元素包含修改时间
4. 我们不能修改 **st_ctim**，因为调用 utimes 函数时，此字段会自动更新

```c
#include <sys/time.h>

int utimes(const char *pathname, const struct timeval times[2]);
```

---

```c
struct
{
	time_t tv_sec;			// seconds
	long   tv_usec;			// microseconds
};
```

### 4.20 修改文件时间实例

1. 这个例子获取文件的当前 atim 和 mtim，并调用 futimens 设置。最后 atim 和 mtim 不变，而 ctim 改变了。因为我们修改了文件的 i节点

```c
#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int i, fd;
    struct stat statbuf;
    struct timespec times[2];

    for (i = 1; i != argc; ++i)
    {
        if (stat(argv[i], &statbuf) < 0)
        {
            err_ret("%s: stat error", argv[i]);
            continue;
        }
        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0)
        {
            err_ret("%s: open error", argv[i]);
            continue;
        }
        times[0] = statbuf.st_atimespec;
        times[1] = statbuf.st_mtimespec;
        printf("%s, atim = %ld, mtime = %ld\n", argv[i], statbuf.st_atimespec.tv_sec, statbuf.st_mtimespec.tv_sec);

        if (futimens(fd, times) < 0)
        {
            err_ret("%s: futimens error", argv[i]);
        }
        close(fd);
    }
}
```

## 4.21 mkdir, mkdirat, rmdir

```c
#include <sys/stat.h>

int mkdir(const char *pathname, mode_t mode);
int mkdirat(int fd, const char *pathname, mode_t mode);
```

1. 返回0或-1
2. 创建的文件权限 mode 由进程的文件模式创建屏蔽字修改

```c
#include <unistd.h>

int rmdir(const char *pathname);
```

1. 返回 0 或者 -1

## 4.22 读目录

1. 目录的写权限位和之行为决定了该目录是否能创建新文件以及删除文件， **并不表示能否写目录本身，只有内核才可以写目录**

```c
#include <dirent.h>

DIR *opendir(const char *pathname);
DIR *fdopendir(int fd);
									// 返回指针或者 NULL

struct dirent *readdir(DIR *dp);
									// 返回指针或者 NULL

void rewinddir(DIR *dp);
int closedir(DIR *dp);
									// 返回0或-1
long telldir(DIR *dp);
									// 与 dp 关联的目录的当前位置

void seekdir(DIR *dp, long loc);
```

### DIR 实例

```c
#include "../apue.h"
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;

static int myftw(char *, Myfunc *);

static int dopath(Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char **argv)
{
    int ret;
    if (argc != 2)
        err_quit("usage: ftw <starting-pathname>");

    ret = myftw(argv[1], myfunc);
}

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

static char *fullpath;
static int  pathlen;

static int myftw(char *pathname, Myfunc *func)
{
    fullpath = path_alloc(&pathlen);
    if (pathlen <= strlen(pathname))
    {
        pathlen       = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc failed");
    }
    strcpy(fullpath, pathname);
    return (dopath(func));
}

static int dopath(Myfunc *func)
{
    struct stat   statbuf;
    struct dirent *dirp;
    DIR           *dp;
    size_t        ret, n;
    if (lstat(fullpath, &statbuf) < 0)
        return (func(fullpath, &statbuf, FTW_NS));
    if (S_ISDIR(statbuf.st_mode) == 0)
        return (func(fullpath, &statbuf, FTW_F));
    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
        return (ret);

    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen)
    {
        pathlen *= 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc failed");
    }
    fullpath[n++] = '/';
    fullpath[n]   = 0;
    if ((dp = opendir(fullpath)) == NULL)
        return (func(fullpath, &statbuf, FTW_DNR));

    while ((dirp = readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name, ".") == 0
            || strcmp(dirp->d_name, "..") == 0)
            continue;

        strcpy(&fullpath[n], dirp->d_name);
        if ((ret = dopath(func)) != 0)
            break;
    }
    fullpath[n - 1] = 0;
    if (closedir(dp) < 0)
        err_ret("can't close dir %s", fullpath);
    return (ret);
}

static int myfunc(const char *pathname, const struct stat *statptr, int type)
{
    switch (type)
    {
        // 判断文件类型，有两种方法：
        // 1. 通过 S_ISDIR 之类的宏
        // 2. 像下面这样通过 switch case 来实现
        // #define S_ISBLK(m)      (((m) & S_IFMT) == S_IFBLK)     /* block special */
        case FTW_F:
            switch (statptr->st_mode & S_IFMT)
            {
                case S_IFREG:
                    nreg++;
                    break;
                case S_IFBLK:
                    nblk++;
                    break;
                case S_IFCHR:
                    nchr++;
                    break;
                case S_IFIFO:
                    nfifo++;
                    break;
                case S_IFLNK:
                    nslink++;
                    break;
                case S_IFSOCK:
                    nsock++;
                    break;
                case S_IFDIR:
                    // dir should have type = FTW_D
                    err_dump("for S_IFDIR for %s", pathname);
            }
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            err_ret("can't read directory %s", pathname);
        case FTW_NS:
            err_ret("stat error for %s", pathname);
        default:
            err_dump("unknown type %d for pathname %s", type, pathname);
    }

    return (0);
}

```

## 4.23 chdir, fchdr, getcwd

```c
#include <unistd.h>

int chdir(const char *pathname);
int fchdir(int fd);
```

1. 返回 0 或者 -1

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    if (chdir("/tmp") < 0)
    {
        err_sys("chdir failed");
    }
    printf("chdir to /tmp succeeded\n");

    exit(0);
}
```

```c
#include <unistd.h>

char *getcwd(char *buf, size_t size);
```

1. 成功返回 buf，失败返回 NULL

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    char *ptr;
    int size;
    if (chdir("/Users/dhy/tmp") < 0)
        err_sys("chdir failed");
    ptr = (char *)path_alloc(&size);
    if (getcwd(ptr, size) == NULL)
        err_sys("getcwd failed");
    printf("cwd = %s\n", ptr);
    exit(0);
}
```

## 4.24 设备特殊文件

1. 每个文件系统所在的存储设备都由其主、次设备号表示。设备号所使用的数据类型是基本系统数据类型 dev_t
2. 系统中与每个文件名关联的 st_dev 值是文件系统的设备号，该文件系统包含了这一文件名以及与其对应的 i 节点
3. **只有字符特殊文件和块特殊文件才有 st_rdev 值，此值包含实际的设备号**
4. 主设备号标志设备驱动程序，次设备号标志特定的子设备
5. 可以通过 major 和 minor 来访问主、次设备号

```c
#include <zconf.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int         i;
    struct stat buf;
    for (i = 1; i < argc; ++i)
    {
        printf("%s: ", argv[i]);
        if (stat(argv[i], &buf) < 0)
        {
            err_ret("stat error");
            continue;
        }
        printf("dev = %d/%d\n", major(buf.st_dev), minor(buf.st_dev));
        if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
        {
            printf("(%s) rdev = %d/%d", (S_ISCHR(buf.st_mode)) ? "character" : "block",
                   major(buf.st_rdev), minor(buf.st_rdev));
        }
        printf("\n");
    }
    exit(0);
}
```

## 习题

### 4.1

>用 stat 函数替换图 4-3 程序中的 lstat 函数，如若命令行参数之一是符号链接，会发生什么变化？

stat 将跟随符号链接获取符号链接指向的文件的对应信息，而不是符号的信息

### 4.2 

>如果文件模式创建屏蔽字是 777 （八进制），结果会怎样？用 shell 的 umask 命令验证该结果

```bash
umask
# 0022
umask -S
# u=rwx,g=rx,o=rx
umask 777
umask -S
# u=,g=,o=
echo 'Hello World!' > hello
ls -l hello
#---------- 1 meik meik 13 5月   2 11:22 hello
#$ cat hello
#cat: hello: 权限不够
```

### 4.4

>创建文件 foo 和 bar 后，运行图 4-9 的程序，将发生什么情况？

1. 由于文件已经被创建，所以调用 creat 函数会失败。而 umask 不会影响已经创建的文件。
2. 会议一下 3.4，creat 函数等同于 `open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);`。所以文件会被截断

```bash
cat 'foo' > foo
cat 'bar' > bar
ll | egrep 'foo|bar'
#-rw-r--r--  1 dhy  staff     0B Dec 31 20:05 bar
#-rw-r--r--  1 dhy  staff     0B Dec 31 20:05 foo
./a.out          
ll | egrep 'foo|bar'    
#-rw-r--r--  1 dhy  staff     0B Dec 31 20:06 bar
#-rw-r--r--  1 dhy  staff     0B Dec 31 20:06 foo
```

### 4.5

>4.12 节中讲到一个普通文件的大小可以为 0，同时我们又知道 st_size 字段是为目录或符号链接定义的，那么目录和符号链接的长度是否可以为 0 ？

1. 因为目录中总是包括。和 .. ，因此目录的长度不可能为 0 。
2. 符号链接的长度是其指向的文件的文件名长度。

### 4.6

>编写一个类似 cp (1) 的程序，它复制包含空洞的文件，但不将字节 0 写到输出文件中去。

>下面测试了一下 read 和 write 得出一下几个结论

1. read 到 buf 中的结果不能使用 printf 打印，因为 printf 是处理字符串的方法。必须以 '\0' 作为结尾。而我们读取到 buf 的数据是不包含的。
2. read 数据时，包含文件空洞的数据也会被读取到缓冲区

write cnt 11
offset = 0
offset = 1035
write cnt 11
offset = 0
read cnt 1046, buf = hello world

cat file.hoe                
hello worldhello world%     

```c
#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int fd = open("file.hoe", O_RDWR | O_TRUNC | O_CREAT, 0755);
    if (fd == -1)
        err_sys("open file error");
    ssize_t wn = write(fd, "hello world", 11);
    printf("write cnt %zd\n", wn);

    off_t offset = lseek(fd, 0, SEEK_SET);
    printf("offset = %lld\n", offset);
    char    buf[MAXLINE];
    ssize_t rn   = read(fd, buf, MAXLINE);
    // 下面这样输出是错误的
    // printf("read cnt %zd, buf = %s\n", rn, buf);
    offset = lseek(fd, 1024, SEEK_END);
    printf("offset = %lld\n", offset);
    wn = write(fd, "hello world", 11);
    printf("write cnt %zd\n", wn);

    offset = lseek(fd, 0, SEEK_SET);
    printf("offset = %lld\n", offset);
    rn = read(fd, buf, MAXLINE);
    printf("read cnt %zd, buf = %s\n", rn, buf);
}
```

### 4.7

>在 4.12 节 ls 命令的输出中， core 和 core.copy 的访问权限不同，如果创建两个文件时 umask 没有变，说明为什么会出现这种差别。

umask 是进程级的，而 shell 执行命令时会启动一个新的进程并调用 `exec` 命令。所以 shell 和 cat 是在两个独立的进程中，也包含了独立的 umask

### 4.8

[How are directory structures stored in UNIX filesystem?](https://superuser.com/questions/520107/how-are-directory-structures-stored-in-unix-filesystem)

### 4.9

>图 4-20 中显示 unlink 函数会修改文件状态更改时间，这是怎样发生的？

unlink 函数会将文件的引用次数减一，而这个引用次数是存放在 inode 节点中的。

### 4.10

>4.22 节中，系统对可打开文件数的限制对 myftw 函数会产生什么影响？

myftw 使用 opendir 打开文件并递归的计算文件数量，对打开文件数的限制会使得部分文件在调用 opendir 时无法正确打开。进而影响该文件以及该文件内部的所有文件统计失败

### 4.16

```c
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include "../../apue.h"

int main(int argc, char **argv)
{
    char buf[PATH_MAX];
    char filename[PATH_MAX];
    int fd = open(argv[1], O_CREAT, S_IRWXU);
    if (fd < 0)
        err_sys("error open file :%s", argv[1]);

    int deep = 1;
    while (getcwd(buf, PATH_MAX) != NULL)
    {
        printf("current word dir: %s\n", buf);
        sprintf(filename, "%s%d", "dir", deep++);
        if (mkdir(filename, S_IRWXU))
            err_sys("error mkdir : %s", filename);
        if (chdir(filename) < 0)
            err_sys("error chdir : %s", filename);
    }
    printf("%s\n", strerror(errno));
    // Result too large
}
```

### 4.17

>3.16 节中描述了 /dev/fd 特征。如果每个用户都可以访问这些文件，则其访问权限必须为 rw-rw-rw- 。有些程序创建输出文件时，先删除该文件以确保该文件名不存在，忽略返回值。

```c
unlink(path);
if ((fd = creat(path, FILE_MODE)) < 0)
    err_sys("...");
```

1. `/dev/fd` 关闭了其他用户的写权限，因此 unlink 会失败，我们应当仔细思考一下为什么关闭了 `dev` 的写权限会导致我们无法修改 `/dev/fd` 下的内容 
2. **删除 `/dev/fd/0` 文件相当于对 `/dev/fd` 进行写操作，而不是对 `/dev/fd/0` 进行写操作**
3. 我们在文件夹 `dev/fd` 下保存了目录中的文件的 inode 节点，当我们删除 `/dev/fd/0` 时，需要将 `/dev/fd/0` 的 inode 引用次数-1并且删除 `/dev/fd` 下的这个 inode 节点。所以需要文件的写权限
