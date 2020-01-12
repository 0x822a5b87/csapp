# 进程关系

## 9.2 终端登录

### BSD 终端登录

>/etc/ttys

1. init以一个空环境调用getty。getty以终端名（如TERM=foo，其中终端foo的类型取自gettytab文件）和在gettytab中说明的环境字符串为login创建一个环境（envp参数）
2. login 程序得到了用户名，所以可以调用 getpwnam 获取改用户的登录口令的加密文件。然后可以获取用户输入的密码并判断是否允许用户登录
3. 在密码验证通过之后，login 会修改目录（chdir），修改该终端所有权（chown），修改终端访问权限（chmod）等。
4. 至此，登录用户的 shell 开始正常执行

### MacOS

1. MacOS 的 init 是基于 launchd 完成的。

### Linux

>/ect/inittab

## 9.3 网络登录

1. 通过串行终端登录至系统和经由网络登录至系统两者之间的主要（物理上的）区别是：网络登录时，在终端和计算机之间的连接不再是点到点的。在网络登录情况下，login仅仅是一种可用的服务
2. `9.2` 提到的终端登录，init 知道哪些设备可以用来登录，并为每个设备生成一个 getty 进程。但是对于网络连接，所有的登录都经由内核的网络接口驱动，并且不知道会有多少个连接。

### BSD 网络登录

1. 在 BSD 中，有一个 inetd 进程用于等待大多数网络连接
2. inetd 进程由 init 进程通过 /etc/rc 启动，它的父进程为 init
3. inetd 监听 TCP/IP 请求，当一个请求到达时，他通过 fork 生成子进程，并在子进程中通过 exec 生成合适的程序。例如，如果 TCP 的应用层是一个 telnet，那么生成一个服务 telnet 协议的程序 telnetd
4. **当通过终端或网络登录时，我们得到一个登录shell，其标准输入、标准输出和标准错误要么连接到一个终端设备，要么连接到一个伪终端设备上**

### MacOS

1. inetd 是从 launchd 运行的

### linux

1. 部分使用 `xinetd` 代替 `inetd`

## 9.4 进程组

```c
pid_t getpgrp(void);
```

1. 获取当前进程的进程组，返回进程组ID或者-1
2. **每个进程组有一个组长进程。组长进程的进程组ID等于其进程ID**
3. 进程组组长可以创建一个进程组、创建改组中的进程， **然后终止**。只要一个进程组中有一个进程存在，这个进程组就存在。

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    pid_t pgid = getpgrp();
    pid_t pid  = getpid();
    pid_t pgid2 = getpgid(pid);
    printf("pgid = %ld, pgid2 = %ld, pid = %d\n", ((long) pgid), ((long) pgid2), pid);
}
```

---

```c
int setpgid(pid_t pid, pid_t pgid);
```

1. 设置 pid 的进程的进程组id 为 pgid，如果两个参数相等，则 pid 变为进程组的组长
2. pid 为 0 则使用调用者的 pid
3. 一个进程只能为它自己或者它的子进程设置进程组ID。在它的子进程调用了 exec 之后，它不在更改子进程的进程组ID

## 9.5 会话(session)

1. 会话是一个或多个进程组的集合；
2. 在 shell 中，使用 `|` 可以生成进程组，使用 `&` 可以生成会话。例如，`proc1 | proc2 & proc3 | proc4` 将会生成一个会话，包含两个进程组分别是 `proc1 和 proc2`，`proc3 和 proc4`


```c
#include <unistd.h>

pid_t setsid(void);
```

1. 设置会话ID，返回进程组的ID或-1
2. 如果调用此函数的不是一个进程组的组长，那么：
	- 进程会成为一个新的进程组的组长进程
	- 进程变为新会话的 session leader
	- 该进程没有控制终端
3. 如果进程是进程组的组长，那么函数返回出错，所以我们一般使用 fork() 后终止父进程，在子进程中调用这个方法。因为子进程的ID是新生成的，可以保证不是进程组组长

```c
pid_t getsid(pid_t pid);
```

1. 获取 pid 对应的 **session leader** 的进程组ID或 -1
2. 因为规范只说明了 session leader 没有说明会话有类似进程ID和进程组ID一样的会话ID

## 9.6 控制终端

## 9.10
