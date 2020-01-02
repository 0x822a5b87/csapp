# 系统数据文件和信息

## 6.1 引言

1. UNIX 运行需要大量与系统有关的数据文件，例如 /etc/passwd
2. 文件使用 ASCII 存储，我们希望能以非ASCII文本格式存放这些文件，同时向其他的文件格式的应用程序提供接口

## 6.2 口令文件

1. 由于历史原因，口令文件是 `/etc/passwd`；
2. 口令文件字段之间用 `:` 分割

```c
struct passwd *getpwuid(uid_t uid);
struct passwd *getpwnam(const char *name);
```

1. 根据 uid 或者 name 获取 pwd，返回指针或者 NULL

```c
#include <pwd.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    struct passwd *pwd = getpwnam(argv[1]);
    printf("%s\n", pwd->pw_shell);
    struct passwd *uid = getpwuid(pwd->pw_uid);
    printf("%s\n", uid->pw_shell);
}
```

---

>如果要查看的只是登录名或用户ID，那么这两个POSIX.1函数能满足要求

```c
struct passwd *getpwent(void);

void setpwent(void);
void endpwen(void);
```

---

>下面给出了一个 getpwnam 的实现

1. The setpwent() function rewinds to the beginning of the password database.
2. The endpwent() function is used to close the password database after all processing has been performed.

```c
#include "pwd.h"
#include "stddef.h"
#include "string.h"

struct passwd *getpwnam(const char *name)
{
    struct passwd *ptr;
    setpwent();
    while((ptr = getpwent()) != NULL)
        if (strcmp(name, ptr->pw_name) == 0)
            break;

    endpwent();
    return (ptr);
}

```

## 6.3 阴影口令

1. 加密口令是单向加密的；
2. 部分系统为了增加加密口令的破解难度，将加密口令存放在 `/etc/shadow` 文件中

```c
struct spwd *getspnm(const char *name);
struct spwd *getspent(void);
```

1. 获取一个加密口令，返回指针或者 NULL

```c
void setspent(void);
void endspent(void);
```

## 6.4 组文件

1. 组文件存放在 `/etc/group` 下
2. `struct group` 包含一个 `char **gr_mem` 成员。每个指针一个属于该组的用户名；该数组以 null 结尾

---

```c
struct group *getgrgid(gid_t gid);
struct group *getgrnam(const char *name);
```

1. 返回指针或者 NULL

---

```c
struct group *getgrent(void);

void setgrent(void);
void endgrent(void);
```

1. 返回下一个组或者 NULL

## 6.5 附属组ID

1. 除了属于口令文件组ID中的组，也可以属于额外的最多16个附属组；
2. 权限检查时除了检查有效组，也会检查附属组；

```c
int getgroups(int gidsetsize, gid_t grouplist[]);

int setgroups(int ngroups, const gid_t grouplist[]);
int initgroups(const char *username, gid_t basegid);
```

1. getgroups 将进程所属用户的各附加组添加到 grouplist 中，最多添加 gidsetsize 个：返回实际添加数量；
2. 我们可以通过 getgroups(0, NULL); 来获取实际的附属组ID数量
3. setgroups 为调用进程设置附属组ID表

```c
#include <grp.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int gcnt = getgroups(0, NULL);
    printf("gcnt = %d\n", gcnt);
    gid_t gids[gcnt];
    gcnt = getgroups(gcnt, gids);
    printf("gcnt = %d\n", gcnt);

    for (int i = 0; i < gcnt; ++i)
    {
        struct group *gp = getgrgid(gids[i]);
        printf("%s\n", gp->gr_name);
    }
}
```

## 6.7 其他数据文件

>一般情况下，对于数据文件至少提供三个函数

1. get 函数：读取下一个记录，如果需要还会打开该文件
2. set 函数：打开相应数据文件（如果文件尚未打开），然后 rewind 该文件
3. end 函数：关闭文件。
4. 另外，如果支持 k-v，还会提供一些 getbykey 的操作，例如 `getpwnam`

## 6.9 系统标志

```c
int uname(struct utsname *name);
```

1. 返回非负值或者 -1

```c
#include "../apue.h"
#include "sys/utsname.h"

int main(int argc, char **argv)
{
    struct utsname name;
    if (uname(&name) < 0)
        err_sys("uname error");
    printf("%s\n%s\n%s\n%s\n%s\n",
           name.machine, name.nodename,
           name.release, name.sysname,
           name.version);
    
    //x86_64
    //HANGYUDU-MB0
    //18.7.0
    //Darwin
    //Darwin Kernel Version 18.7.0: Tue Aug 20 16:57:14 PDT 2019; root:xnu-4903.271.2~2/RELEASE_X86_64
}

```

## 6.10 时间和日期

```c
time_t time(time_t *calptr);
```

1. 返回时间值或者 -1，如果 calptr 非空，则 calptr 也存放了时间

```c
int clock_gettime(clockid_t clock_id, struct timespec *tsp);
```

1. 获取指定时钟的时间
2. struct timespec 下的 tv_nsec 表示的 nanosec

```c
#include <sys/time.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    time_t t = time(NULL);
    printf("%ld\n", t);
    // 1577966439

    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) < 0)
        err_sys("clock_gettime error");

    printf("%ld/%ld\n", ts.tv_sec, ts.tv_nsec);
    // 1577967112/479804000
}
```

---

```c
int clock_getres(clockid_t clock_id, struct timespec *tsp);
```

1. 返回 0 或者 -1

## 习题

```c
#include <time.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
	// return a pointer to static data and hence are not thread-safe.
    timeinfo = localtime ( &rawtime );

    char buf[MAXLINE];
    if (strftime(buf, MAXLINE, "%a %b %d %H %M %S %Z %Y", timeinfo) < 0)
        err_sys("strftime error");

    printf("%s\n", buf);
}
```
