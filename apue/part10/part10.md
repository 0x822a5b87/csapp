# 信号

## 10. 引言

1. 信号是软件中断

## 10.2 信号概念

1. 每个信号都有一个名字，以 SIG 开头，包含在头文件 `<signal.h>` 中
2. 实际上，UNIX 的实现将信号定义在另一个头文件中，然后通过 <signal.h> 去包含此文件。这是因为内核 include 那些对用户级程序有意义的文件是 bad practise，所以 一般在内核头文件中定义，在用户头文件中去 inlcude 内核头文件
3. 编号为 0 的信号是空信号

## 10.3 函数 signal

```c
#include <signal.h>

void (*signal(int signo, void (*func)(int))) (int);

// equivalent to

typedef void (*sig_t) (int);

sig_t signal(int sig, sig_t func);
```

1. 返回以前的信号处理配置或者 SIG_ERR
2. signal 函数由 ISO C 定义，但是 ISO C 不涉及多进程，进程组等，所以它对信号的定义非常含糊，以至于对 UNIX 系统基本毫无作用
3. 因为 signal 的语义与实现有关， **所以最好使用 sigaction 函数代替 signal 函数**
4. signo 参数是信号名(定义在 <signal.h> 中的常量)，func 则是常量 SIG_IGN, SIG_DFL 或者一个函数指针

### example

```c
#include "../apue.h"

static void sig_usr(int);

int main(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("can't catch SIGUSR1");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("can't catch SIGUSR2");

    for (;;)
        pause();
}

static void sig_usr(int signo)
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        err_dump("received signal %d\n", signo);
}
```

```bash
./a.out
#[1] 85741
kill -USR1 85741
#received SIGUSR1
kill -USR2 85741
#received SIGUSR2
kill 85741					# 发送 SIGTERM
#Terminated ./a.out
```

### 程序启动

1. **exec 函数将原先设置为要捕捉的信号都更改为默认动作，其他信号则保持不变。** 因为一个进程原先要捕捉的信号，当其执行了一个新程序之后，就不能再捕捉了，因为信号捕捉函数的地址可能已经失效了。
2. shell 会自动的将 `cc main.c &` 这种后台进程的 中断和退出信号设置为忽略，这样我们在发送这两个信号时就不会关闭后台进程
3. signal 函数有个很严重的问题，必须要改变信号才能知道当前的信号是什么

```c
// 仅当 SIGINT 和 SIGQUIT 没有被设置为忽略时才会修改信号捕捉函数
void sig_int(int), sig_quit(int);

if (signal(SIGINT, SIG_IGN) != SIG_IGN)
	signal(SIGINT, sig_int);
if (signal(SIGQUIT, SIG_IGN) != SIG_IGN)
	signal(SIGQUIT, sig_quit);
```

### 进程创建

1. 子进程进程父进程的信号处理方式，因为 fork() 会复制整个虚拟内存，所以函数指针是有意义的

## 10.5 中断的系统调用

1. 早期 UNIX 有一个系统特性：如果进程执行了一个 **低速系统调用的阻塞期间** 收到一个信号，则该系统调用就被中断不再继续执行。并且，该系统调用返回出错，其 errno 设置为 EINTR。
2. <1> 中被中断的是系统调用，而不是系统函数；
3. 对于 read、write 系统调用，如果 read 系统调用已经接收并传送数据到应用程序缓冲区，但尚未接收到应用程序请求的全部数据，此时被中断，操作系统可以认为该系统调用失败；另一种方式是允许系统调用成功返回，返回值是已经收到到的数据量
4. 被中断的系统调用必须显示的处理出错返回：

```c
again:
	if ((n = read(fd, buf, BUFFSIZE)) < 0)
	{
		if (errno == EINTR)
		{
			goto again;
		}
	}
```
5. 为了帮助应用程序使其不必处理被中断的系统调用，4.2BSD引进了某些被中断系统调用的自动重启动。自动重启动的系统调用包括：ioctl、read、readv、write、writev、wait 和waitpid
6. 因为这种自动重启动的处理方式也会带来问题，某些应用程序并不希望这些函数被中断后重启动。为此4.3BSD允许进程基于每个信号禁用此功能。

## 10.6 可重入函数

1. 进程在执行时，可能会被信号中断并进入信号的处理逻辑，在处理完之后返回执行原来的指令（如果信号处理程序中没有 exit 或者 longjmp 之类的的指令的话）
2. 在任意时刻都可能接收到信号，所以我们不能确定当捕捉到信号时进程在执行哪一条指令
3. SUS 说明了信号处理程序中保证调用安全的函数，这些函数被称之为可重入的和异步引号安全的
4. 标准I/O库很多实现都以不可重入的方式使用全局数据结构；
5. **由于每个线程只有一个 `errno` 变量，所以信号处理程序可能会修改原来的值。所以，作为一个通用的规则，信号处理程序有义务在程序开始时保存 errno，并在结束时恢复 errno**


```c
#include <pwd.h>
#include "../apue.h"

static void my_alarm(int signo)
{
    struct passwd *rootptr;
    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL)
    {
        err_sys("getpwnam(root) error");
    }
    printf("getpwnam(root)\n");
    alarm(1);
}

int main(int argc, char **argv)
{
    struct passwd *ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);
    for(;;)
    {
        if ((ptr = getpwnam("dhy")) == NULL)
        {
            err_sys("getpanam error");
            exit(0);
        }
        if (strcmp(ptr->pw_name, "dhy") != 0)
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
    }
}
```

## 10.7 SIGCLD 语义

1. [What is the difference between SIGCLD and SIGCHLD signals?](https://stackoverflow.com/questions/25960248/what-is-the-difference-between-sigcld-and-sigchld-signals)
2. SIGCLD 是 System V 的信号名， SIGCHLD 是 BSD 的信号名
3. SIGCHLD ： 子进程状态改变后产生此信号，父进程需要调用 wait 函数检测
4. SIGCLD ：
	- 如果进程明确的设置该信号为 SIG_IGN，则调用的子进程不产生僵尸进程
	- 如果将 SIGCLD 配置为捕捉(也就是说调用 `signal(SIGCLD, cld_handler)`)，则内核应立即检查是否有子进程准备好等待，如果是这样，则调用 SIGCHLD 处理程序
5. 下面的这段代码，会一直输出 SIGCLD received。因为在 `sig_cld` 中调用了 signal(SIGCLD, sig_cld)。那么根据 <4> 内核会检查是否有正在等待的子进程，而因为我们正在处理 SIGCLD 信号，所以它会产生再次调用 `sig_cld`，于是程序一直无法正常退出。
6. 为了解决 <5> 提到的问题，我们应该将 signal 函数放到 wait 函数之后，这样当我们执行 signal 时，子进程已经退出了，我们依旧没有正在等待的子进程。

```c
// 这段代码在 macOS 无效，因为 macOS 根本就没有 SIGCLD 这个信号

#include "../apue.h"

static void sig_cld(int);

int main(int argc, char **argv)
{
    pid_t pid;

#ifdef SIGCLD
    if (signal(SIGCHLD, sig_cld) == SIG_ERR)
        err_sys("signal error");
#endif
    if ((pid = fork()) < 0) {
        perror("signal error");
    } else if (pid == 0) {
        sleep(2);
        _exit(0);
    }

    pause();
    exit(0);
}

static void sig_cld(int signo)
{
    pid_t pid;
    int status;
    printf("SIGCLD received\n");

#ifdef SIGCLD
    if (signal(SIGCLD, sig_cld) == SIG_ERR)
        err_sys("signal error");
#endif
    if ((pid = wait(&status)) < 0)
        perror("wait error");

    printf("pid = %d\n", pid);
}
```

## 10.8 可靠信号术语和语义

1. 当一个信号产生时， **内核通常在 `进程表` 中以某种形式设置一个标志位**
2. 当对信号产生了这种动作，我们说向进程传递了一个信号。在信号 **产生(generation)** 和 **传递(delivery)** 之间的时间间隔内，称信号是 **pending** 的
3. 进程可以 **阻塞信号传递**。如果为进程产生了一个阻塞的信号，而且对该信号的动作是默认动作或者捕捉该信号，则为该进程 **将此信号保持为 pending 状态**，直到该进程取消了对此信号的阻塞，或者对此信号的行动修改为忽略
4. <3> 使得我们有一个能力：假设我们和某一个信号的处理函数会访问一个共享数据，那么我们可以先屏蔽这个信号，那么当我们在函数中处理共享数据时收到信号，就不会进入信号处理程序，而是等我们的函数处理完，解除对该信号的处理时才进入信号处理程序。
5. **除非支持 POSIX.1 实时扩展，否则UNIX不对信号排队，而是只传递信号一次**
6. 如果有多个信号需要传递给一个进程，我们应当在其他信号之前传递与进程的当前状态有关的信号。
7. 进程可以使用 `sigprocmask` 来检测和更改其关键字

## 10.9 kill, raise

```c
int kill(pid_t pid, int signo);
int raise(int signo);
```

1. kill 函数发送信号给进程或者进程组，raise 函数向自身发送信号，等价于 kill(getpid(), signo)；返回 0 或者 -1
	- pid < 0 发送给进程组ID等于 pid 绝对值，并且发送进程具有想起发送信号的权限的进程
	- pid > 0 发送给 pid
	- pid == 0 发送给调用进程的统一进程组的所有进程
	- pid == -1 发送给调用进程所有有权发送进程的进程
2. 对于非 root 用户，有权限的基本规则是，发送者的实际用户ID或有效用户ID等于接受者的实际用户ID或有效用户ID
3. signo == 0 代表空信号，kill(pid, 0) 将执行正常的错误检查，但是不发送信号
	- 可以用来检测 pid 是否存在，不存在则返回 -1
	- 但是 pid 存在，并不代表现在的 pid 仍然是我们想象中的那个进程

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    pid_t pid;
    pid_t pgrpid;

    if ((pid = fork()) == 0)
    {
		// 子进程和父进程在一个进程组
        pgrpid = getpgrp();
        printf("child pid = %ld, pgrpid = %ld\n",(long) getpid(), (long) pgrpid);
    }
    else
    {
		// 父进程是子进程所在进程的进程组组长
        pgrpid = getpgrp();
        printf("parent pid = %ld, pgrpid = %ld\n", (long) getpid(), (long) pgrpid);
    }
}
```

## 10.10 alarm，pause

```c
unsigned int alarm(unsigned int seconds);
```

1. seconds 秒后向调用者发送一个 SIGALRM 信号，默认会终止调用进程；
2. 返回 0 或者以前设置闹钟时间的剩余秒数
3. 每个进程只能有一个闹钟时间
4. alarm(0) 会取消之前设置的闹钟

---

```c
int pause(void);
```

1. pause() 使调用进程挂起直到捕捉到一个信号
2. 返回 -1，errno 设置为 EINTR
3. **只有执行了一个信号处理程序并从其返回时，pause才返回。在这种情况下，pause返回−1， errno设置为EINTR。**
4. 下面的 sleep 实现存在几个问题：
	- alarm(seconds) 会擦除 sleep1 之前的闹钟调用
	- 程序修改了 SIGALRM 的信号处理函数，可以通过保存 signal 的返回值，在返回前重置为原配置
	- 在第一次调用 alarm 和 pause 之间存在 Race

```c
// sleep 简化而不完整的实现
#include "../apue.h"

static void sig_alrm(int signo)
{
    // nothing-to do
}

unsigned int sleep1(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        return (seconds);
    alarm(seconds);
    pause();
    return (alarm(0));
}
```

>通过 longjmp 可以解决 alarm 和 pause 之间的 Race
><br/>
>在调用 alarm 之前设置了跳转点，那么不管怎么样，只要进入了  SIGALRM 的信号处理函数我们一定会跳转到 setjmp 的位置
><br/>
>具体可以参考 [setjmp 的正确使用](https://blog.codingnow.com/2010/05/setjmp.html)

```c
#include <setjmp.h>
#include "../apue.h"

static jmp_buf env_alrm;

static void sig_alrm(int signo)
{
    longjmp(env_alrm, 1);
}

unsigned int sleep2(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        return (seconds);
    if (setjmp(env_alrm) == 0)
    {
        alarm(seconds);
        pause();
    }
    return (alarm(0));
}

```
