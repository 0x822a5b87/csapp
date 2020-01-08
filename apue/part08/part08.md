# 进程控制

## 8.2 进程标识

1. 每个进程都有一个 **非负整型** 标识唯一进程ID；应用程序可以把进程ID作为名字的一部分来创建出一个唯一的文件名，很多任务会在一个叫 pid 的文件中写入自己的进程ID，并在退出的时候通过 `kill pid` 来杀死这个进程。
2. 进程ID是可复用的，但是一般在一个进程结束很久之后才会把这个进程ID赋值给其他进程；
3. **系统中有一些专用进程，具体细节随实现而不同**
4. 调度进程：一般 pid 为 0，也称之为交换进程（swapper）。是内核的一部分，也被称之为系统进程；
5. init 进程：一般 pid 为 1，在自举过程结束时由内核调用，负责在自举内核后启动一个 UNIX 系统 
6. init 进程绝不会终止，它是一个普通的用户进程（他不是内核中的系统进程），但是以 root 权限运行。

```c
pid_t getpid(void);
pid_t getppid(void);

uid_t getuid(void);
			// 进程的实际用户ID
uid_t geteuid(void);
			// 进程的有效用户ID

gid_t getgid(void);
			// 进程的有效组ID
gid_t getegid(void);
			// 进程的实际组ID
```

```c
#include <grp.h>
#include <pwd.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    uid_t uid  = getuid();
    uid_t euid = geteuid();

    printf("uid = %d, euid = %d\n", uid, euid);

    struct passwd *up  = getpwuid(uid);
    struct passwd *eup = getpwuid(euid);
    printf("u name = %s, eu name = %s\n", up->pw_name, eup->pw_name);

    gid_t gid  = getgid();
    gid_t egid = getegid();

    printf("gid = %d, egid = %d\n", gid, egid);

    struct group *g  = getgrgid(gid);
    struct group *eg = getgrgid(egid);
    printf("g name = %s, eg name = %s\n", g->gr_name, eg->gr_name);
}
```

```bash
./a.out
#uid = 501, euid = 501
#u name = dhy, eu name = dhy
#gid = 20, egid = 20
#g name = staff, eg name = staff
```

```bash
sudo ./a.out
#uid = 0, euid = 0
#u name = root, eu name = root
#gid = 0, egid = 0
#g name = wheel, eg name = wheel
```

## 8.3 fork

```c
pid_t fork(void);
```

1. 创建一个子进程：子进程返回0，父进程返回子进程ID，出错返回-1
2. 子进程和父进程继续执行 fork() 调用之后的指令。 **子进程是父进程的副本，它将父进程的数据空间，堆和栈都复制了一份并且不共享。实际上我们会使用 copy-on-write 来优化它**
3. **copy-on-write 使得父进程和子进程共享一片区域，并且内核将这片区域设置为只读。当修改的时候，内核只为修改的那块内存制作一个副本，通常是 `虚拟存储系统中的一页`**
4. strlen 计算不包含 null 的长度， sizeof() 计算包含 null 的长度。但是 sizeof() 是在编译期计算缓冲区的长度
5. 我们关注下输出，当我们使用标准输出时，输出了 `a write to stdout` 和 `before fork`。当我们将标准输出重定向到一个文件时输出了 `a write to stdout` 和两行 `before fork`
6. 两种情况都只输出一行 `a write to stdout`，是因为 write 是不带缓冲的。所以当调用 fork() 是没有缓冲数据被复制的；
7. 标准输出是行缓冲，而文件是全缓冲；所以当使用标准输出时，`before fork` 已经输出，缓冲区是没有数据的；
8. 文件是全缓冲；当重定向到文件时，`before fork\n` 不会输出，所以在调用 fork() 时，缓冲区是包含了数据的，这份数据同样被复制过去了。

```c
#include "../apue.h"

int  globval = 6;
char buf[]   = "a write to stdout\n";

int main(int argc, char **argv)
{
    int   var;
    pid_t pid;

    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
    {
        err_sys("write error");
    }
    printf("before fork\n");
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        globval++;
        var++;
    }
    else
    {
        sleep(2);
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globval, var);
    exit(0);
}
```

```bash
./a.out
#a write to stdout
#before fork
#pid = 62218, glob = 7, var = 89
#pid = 62217, glob = 6, var = 88

touch file
./a.out > file
cat file
#a write to stdout
#before fork
#pid = 63049, glob = 7, var = 89
#before fork
#pid = 63048, glob = 6, var = 88
```

### 文件共享

1. 在重定向父进程的标准输出时，子进程的标准输出也被重定向了
2. 实际上，我们可以认为子进程复制了所有的 fd，假设父进程的 fd 为 pfd，子进程就复制 pfd2 并调用 `dup2(pfd2, pfd)` 指向 pfd 的同一个文件表项
3. 父进程和子进程共享一个偏移量，因为偏移量是存放在文件表项中的；所以在 fork() 完成之后，一般对于文件由 <4>, <5> 两种操作方式
4. 父进程等待子进程完成，那么不论子进程对文件的偏移量做了何种操作，当子进程结束时父进程都可以使用子进程结束时的文件状态；
5. 父进程和子进程各自执行不同的程序段， **在 fork 之后父进程和子进程各自关闭不需要使用的文件描述符**。这种是网络服务进程用得比较多的：例如服务器利用 accepct 接受得到了一个 fd 并且它启动了一个新进程去读写这个 fd 来为客户端提供服务。 **那么它在 accept 的进程中就可以（或者说必须，否则会发生文件句柄泄漏）关闭这个 fd**
6. fork() 失败一般由于：系统已经有了太多进程或者该实际用户ID的进程总数超过了系统限制

```c
#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int f0 = open(__FILE__, O_RDONLY);
    off_t f = lseek(f0, 0, SEEK_END);
    printf("f = %lld, after seek = %lld\n", f, lseek(f0, 0, SEEK_CUR));
	// f = 367, after seek = 367
    dup2(f0, STDIN_FILENO);
    f = lseek(STDIN_FILENO, 0, SEEK_END);
    printf("f = %lld, after seek = %lld\n", f, lseek(f0, 0, SEEK_CUR));
	// f = 367, after seek = 367
}
```

## 8.4 vfork

1. 可移植的应用程序不应该使用这个函数

## 8.5 exit

### 五种正常退出

1. main 函数中执行 return 语句
2. 调用 exit 函数：调用 atexit 登记的程序，关闭所有标准I/O流等。 **不处理文件描述符，多进程以及作业控制**
3. 调用 `_exit` 或者 `_Exit` 
4. 进程的最后一个线程在其启动例程中执行 return
5. 进程的最后一个线程调用 pthread_exit

### 异常退出

1. 调用 abort，他是 <2> 的一种特例
2. 进程收到某些信号，例如 SIGINT
3. 最后一个线程对 **取消** 请求作出响应

>**不管进程如何种植，最后都会执行内核中的同一段代码：关闭描述符，释放存储器等**

### 使用线程

```c
#include <pthread.h>
#include "../apue.h"

void thread(void *);


int main(int argc, char **argv)
{
    pthread_t id;
    int       num = 10;
    int       ret = pthread_create(&id, NULL, (void *) thread, (void *) &num);
    if (ret != 0)
    {
        printf("Create pthread error = [%d]!\n", ret);
        exit(1);
    }
    sleep(1);
}

void thread(void *args)
{
    int pid = *((int *) args);
    printf("hello world from thread %d\n", pid);
}
```

### 孤儿进程(orphan process) 和僵尸进程(zombie process)

[zombie process VS orphan process](https://stackoverflow.com/questions/20688982/zombie-process-vs-orphan-process)

1. 孤儿进程就是父进程比子进程先退出， **当一个进程退出的时候，内核会检查所有所有活动进程，以判断它是否为退出进程的子进程。如果是，那么这个活动进程的父进程修改为 init 进程**
2. 僵尸进程需要满足两个条件： **子进程比父进程先退出并且父进程没有调用 waitpid 来获取子进程的状态**
3. **对于僵尸进程，假设我们不调用 waitpid 来回收子进程的资源，那么理论上来讲，随着我们的主线程执行时间越久，创建的僵尸进程就会越多。**
4. **Zombies only occupy space in the process table. They take no memory or CPU**. However, the process table is a finite resource, and excessive zombies can fill it, meaning that no other processes can launch. Beyond that, they are bothersome clutter, and should be strongly avoided.
5. An orphan is just a process. It will use whatever resources it uses. It is reasonable to say that it is not an "orphan" at all since it has a parent, but I've heard them called that often.
6. 当一个僵尸进程的父进程退出时，它同样会被 init 进程收养，查看 [What happens after the parent of zombie process terminates?](https://stackoverflow.com/questions/17236630/what-happens-after-the-parent-of-zombie-process-terminates)


```c
// orphan process
#include "../apue.h"

int main(int argc, char **argv)
{
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        // child process
        printf("pid: %d\tppid:%d\n",getpid(),getppid());
        sleep(3);
        printf("pid: %d\tppid:%d\n",getpid(),getppid());
        printf("child process exit\n");
        exit(0);
    }
    else
    {
        // parent process
        printf("self_pid = %d, pid = %d\n", getpid(), pid);
        printf("parent process exit\n");
        exit(0);
    }

    // pubic statement
	
	// self_pid = 33885, pid = 33886
	// parent process exit
	// pid: 33886      ppid:33885
	// pid: 33886     ppid:1
	// child process exit
}
```

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
        err_sys("fork error");
    pid_t ppid = getpid();
    if (pid == 0)
    {
        // child process
        printf("child  process, pid = %d, ppid = %d\n", getpid(), getppid());
        printf("child  process exit without waitpid\n");
        exit(0);
    }
    else
    {
        // parent process
        printf("parent process, pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(1);
        char buf[MAXLINE];
        sprintf(buf, "ps -o pid,ppid,state,tty,command | grep %d", pid);
        system(buf);
    }
}
// parent process, pid = 36156, ppid = 1248
// child  process, pid = 36157, ppid = 36156
// child  process exit without waitpid
// 36157 36156 Z+   ttys003  (a.out)
// 36160 36156 S+   ttys003  sh -c ps -o pid,ppid,state,tty,command | grep 36157
// 36162 36160 S+   ttys003  grep 36157
```

#### 测试当僵尸进程的父进程退出时，init 进程是否会收养并回收僵尸进程

```c
#include <stdio.h>
#include <unistd.h>


int main() {
    pid_t child_pid;
    child_pid = fork();
    if (child_pid) { // fork a child, child will exit straight away
        char name[128];
        sprintf(name, "/proc/%d/stat", child_pid);
        char line[2048];

        // read childs /proc/pid/stat, field 3 will give its status
        FILE * fp = fopen(name, "r");

        while (fgets(line, sizeof(line), fp))
            puts(line);

        fclose(fp);

        usleep(5000000);

        // by now the child will have exited for sure, repeat
        fp = fopen(name, "r");

        while (fgets(line, sizeof(line), fp))
            puts(line);

        fclose(fp);

        // make another child to repeat the process and exit the parent
        if (!fork()) {
            usleep(5000000);
            // both parent and child will have exited by now

            fp = fopen(name, "r");

            // this should fail because init has already cleaned up the child
            if (!fp) {
                perror("fopen");
                return -1;
            }

            while (fgets(line, sizeof(line), fp))
                puts(line);

            fclose(fp);
        }

    }

    return 0;
}
```

## wait, waitpid

```c
pid_t wait(int *statloc);
pid_t waitpid(pid_t pid, int *statloc, int options);
```

1. 返回进程ID或者 0 或者 -1
2. 当一个进程 **正常或异常终止时**，内核就向其父进程发送一个 SIGCHLD 信号
3. 如果子进程已经终止并成为一个僵尸进程，那么 wait 立即返回并获取该子进程的状态
4. 如果不关心子进程的状态，可以设置 status 为 NULL。我们可以使用 `<sys/wait.h>` 中定义的宏来查看 status 的状态，宏以 `WIF` 开头(wait if)

### waitpid 的 pid 参数

1. pid == -1，等同于 wait
2. pid > 0，等待 pid
3. pid == 0，等待组ID等于调用进程组ID的任意子进程
4. `pid < -1`，等待组ID等于 pid 绝对值的任意进程

### waitpid 的 options 参数

1. 0
2. WCONTINUED
3. WNOHANG					// 如果 pid 指定的子进程不是立即可用的，那么 waitpid 不阻塞，直接返回 0
4. WUNTRACED				// 如果OS支持，并且 pid 指定的任意子进程处于已经停止状态，并且其状态自停止以来还未报告过，直接返回其状态

### 利用两次fork避免僵死进程

```c
#include "../apue.h"

// 如果调用 fork() 后，既不希望父进程等待子进程终止
// 也不希望子进程变成僵尸进程，等待父进程退出时才被回收
// 可以利用下面这个技巧，fork() 两次来实现
// 其实原理很简单，就是我们创建三个进程：parent, child, second child
// parent 使用 waitpid(child, NULL, 0) 等待 child 退出
// child 立即退出
// 这样 second child 就会被变成孤儿进程并被 init 进程收养
// 之所以要创建 second child，是因为
// 1. 我们不能直接 wait(child, NULL, 0) 来实现，这会阻塞父进程
// 2. 我们也不能在 child 中 sleep 保证 child 会比 parent 先退出
// 所以我们利用两次 fork，保证了退出顺序一定为
// child -> parent
// 而 second child 的退出可能在任意时刻，但是当 child 退出时它会立刻变成 init 的进程的子进程
// 而 child 是立即退出的，所以及时 second child 会有一段时间是僵尸进程
// 也只会持续很短的时间

int main(int argc, char **argv)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        // child process
        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid > 0)
            // child process
            exit(0);

        // second child process
        sleep(2);
        // 必须将 getppid() 转换为 long，因为 int 不一定能存放下 getppid()，而 long 一定可以
        printf("second child, parent pid = %ld\n", (long) getppid());
        exit(0);
    }

    // parent process
    if (waitpid(pid, NULL, 0) != pid)
        err_sys("waitpid error");

    exit(0);
}
```

## 8.7 waitid

```c
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
```

1. 类似于 waitpid，但是更灵活
2. 返回 0 或 -1
3. 用单独的参数表示要等待的子进程所属类型，而不是将进程ID，进程组ID组合成为一个参数
4. WCONTINUED, WEXITED, WSTOPPED 这三个常量之一必须在 options 参数中指定

## 8.8 wait3, wait4

```c
// rusage == resources usage
pid_t wait3(int *statloc, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *statloc, int options, struct ruage *rusage);
```

1. 相对于 waitpid 和 waitid，它允许内核返回终止进程及其所有子进程使用的资源概况。
2. 返回进程ID或者 -1

## 8.9 竞争条件

1. 当多个进程都企图对共享数据进行某种处理， **而最后的结果又取决于进程运行的顺序，我们认为发生了 `竞争条件(race condition)`**
2. 注意，race 和某些并发问题不一样。它依赖于程序运行的顺序，而不是简单的并发问题。很多时候用锁并不能解决 race。例如，我们希望 A，B 两个进程的执行顺序是 A -> B，简单的使用锁只能保证 A 和 B 是原子执行，并不能保证他们的执行顺序；
3. 例如我们在 [利用两次 fork 避免僵死进程](#利用两次fork避免僵死进程) 这个例子中，`sleep(2)` 并不能保证 child 比 second child 先退出

### 一个会产生竞争的例子

>注意，下面的这个例子在我的 mac 上并没有观察到竞争条件

```c
#include "../apue.h"

static void charatatime(char *);

int main(int argc, char **argv)
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        charatatime("output from child\n");
    }
    else
    {
        charatatime("output from parent\n");
    }

    exit(0);
}

static void charatatime(char *str)
{
    char *ptr;
    int  c;

    setbuf(stdout, NULL);
    for (ptr = str; (c = *ptr) != '\0'; ++ptr)
    {
        putc(c, stdout);
    }
}

```

## 8.10 exec

```c
int execl(const char *pathname, const char *arg0, ... /* (char *)0 */ );
int execv(const char *pathname, char *const argv[]);
int execle(const char *pathname, const char *arg0, ...
/* (char *)0, char *const envp[] */ );
int execve(const char *pathname, char *const argv[], char *const envp[]);

int execlp(const char *filename, const char *arg0, ... /* (char *)0 */ );
int execvp(const char *filename, char *const argv[]);

int fexecve(int fd, char *const argv[], char *const envp[]);
```

1. 调用后，该进程被替换为全新的程序，新程序从 main 函数开始执行。
2. **exec 并不创建新的进程，它只是用新程序替换了当前进程的虚拟内存空间**
3. 失败返回-1，成功则不返回（因为它的整个虚拟内存区域都已经全部被替换）
4. [What is the difference between execl and execv?](https://stackoverflow.com/questions/9123697/what-is-the-difference-between-execl-and-execv)
5. 前面四个取路径名作为参数，第四个和第五个以文件名作为参数，最后一个以文件描述符作为参数
6. 当时文件名作为参数时，如果文件名包含了 '/' 则当做路径名；否则在 PATH 环境变量下搜索可执行文件
7. l 代表 list，v 表示 vector
8. 最后一个区别与向新程序传递环境表相关。以e结尾的3个函数（execle、execve和fexecve）可以传递一个指向环境字符串指针数组的指针。其他4个函数则使用调用进程中的environ变量为新程序复制现有的环境
9. 对打开文件的处理与每个描述符的 (close-on-exec) 标志位有关

### 使用list作为参数

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    if (execlp("ls", "-A", NULL) < 0)
        err_sys("execlp error");
}
```

### 使用vector作为参数

```c
#include "../apue.h"

int main(int argc, char **argv)
{
    const char *v[10];
    v[0] = "ls";
    v[1] = "-A";
    if (execlp("ls", v) < 0)
        err_sys("execlp error");
}
```

## 8.11 更改用户ID和组ID

1. unix 系统的权限是按照用户ID和组ID来判断的，所以我们可以通过修改用户ID和组ID来修改用户的权限

```c
int setuid(uid_t uid);
int setgid(gid_t gid);
```

1. 修改用户ID或组ID，返回0或-1

## 8.12 解释器文件

1. 所有的 unix 都支持解释器文件(interpreter file)。它是一个文本文件，以 `#! pathname [ optional-argument ]`

## 8.13 函数 system

```c
int system(const char *cmdstring);
```

1. 如果 cmdstring 为 NULL，我们可以通过返回值非0来判断系统是否支持 system 函数。
2. UNIX 总是支持该函数
3. fork() 失败或者 waitpid 返回除了 EINTR 之外的错误，则 system 返回 -1
4. exec() 执行失败则返回如同执行了 exit(127) 一样
5. 如果 fork, exec, waitpid 都执行成功，则返回shell的终止状态

```c
#include <errno.h>
#include "../apue.h"

int my_system(const char *cmdstring)
{
    pid_t pid;
    int   status = 0;

    if (cmdstring == NULL)
    {
        return (1);
    }

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        execl("/bin/sh", "sh", "-c", cmdstring, NULL);
        _exit(127);
    }
    else
    {
        while (waitpid(pid, &status, 0) < 0)
        {
            if (errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }

    return (status);
}

int main(int argc, char **argv)
{
    my_system("ls");
}

```

## 8.14 process accounting

## 8.15 用户标识

```c
char *getlogin(void);
```

1. 可以获取用户登录时使用的名字，返回指针或者 NULL

```c
#include <pwd.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    char *login_name = getlogin();
    if (login_name == NULL)
        err_sys("error getlogin");

    printf("login name = %s\n", login_name);

    uid_t         uid  = getuid();
    struct passwd *pwd  = getpwuid(uid);

    printf("name = %s\n", pwd->pw_name);
}

```

## 8.16 进程调度

```c
int nice(int incr);
```

1. 调整进程的 nice 值，返回新的 nice 值或者 -1；由于 -1 是合法的返回值，所以在调用 nice 函数之前我们必须清楚 errno。在 nice 函数返回 -1 时需要检查 errno；
2. nice 值越高，程序的优先级越低，因为对 CPU nice；

```c
#include <limits.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    id_t id       = getpid();
    int  priority = getpriority(PRIO_PROCESS, id);
    printf("pri = %d\n", priority);

    int nzero = NZERO;
    nzero = nice(10);
    printf("nice(10) = %d\n", nzero);

    id       = getpid();
    priority = getpriority(PRIO_PROCESS, id);
    printf("after nice(10), pri = %d\n", priority);

    nzero = nice(0);
    printf("nice(0) = %d\n", nzero);

    id       = getpid();
    priority = getpriority(PRIO_PROCESS, id);
    printf("after nice(0) = %d\n", priority);

}
```

## 8.17 进程时间

```c
clock_t times(struct tms *buf);

struct
{
	clock_t tms_utime;		//  user cpu time
	clock_t tms_stime;		//	system cpu time
	clock_t tms_cutime;		//	user CPU time, terminated children
	clock_t tms_cstime;		//	system CPU time, terminated children
};
```

1. 调用后获得 **自己以及已终止子进程** 的时钟时间，用户CPU时间，系统CPU时间
2. 返回时钟时间或者-1。注意，这里返回的不是系统时间戳，在 macos 上返回的是 `157845231906` 是毫秒数/10，在 linux 上返回的是 

```c
#include "../apue.h"
#include <sys/times.h>

static void pr_times(clock_t, struct tms *, struct tms *);

static void do_cmd(char *);

int main(int argc, char **argv)
{
    int i;

    setbuf(stdout, NULL);
    for (i = 1; i < argc; ++i)
    {
        printf("do cmd , i = %d, argc = %d\n", i, argc);
        do_cmd(argv[i]);
    }
    exit(0);
}

static void do_cmd(char *cmd)
{
    struct tms tmsstart, tmsend;
    clock_t    start, end;
    int        status;

    printf("\ncommand:%s\n", cmd);

    if ((start = times(&tmsstart)) == -1)
        err_sys("times error");

    if ((status = system(cmd)) < 0)
        err_sys("system() error");

    if ((end = times(&tmsend)) == -1)
        err_sys("times error");

    pr_times(end - start, &tmsstart, &tmsend);
    pr_exit(status);
}

static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    static long clktck = 0;
    if (clktck == 0)
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
            err_sys("sysconf error");

    printf(" real : %7.2f\n", real / (double) clktck);
    printf(" user : %7.2f\n",
           (tmsend->tms_utime - tmsstart->tms_utime) / ((double) clktck));
    printf(" sys : %7.2f\n",
           (tmsend->tms_stime - tmsstart->tms_stime) / ((double) clktck));
    printf(" child user :%7.2f\n",
           (tmsend->tms_cutime - tmsstart->tms_cutime) / ((double) clktck));
    printf(" child sys :%7.2f\n",
           (tmsend->tms_cstime - tmsstart->tms_cstime) / ((double) clktck));
}

```

## 习题

## 8.1

>在图8-3程序中，如果用exit调用代替_exit调用，那么可能会使标准输出关闭，使printf返回−1。修改该程序以验证在你所使用的系统上是否会产生此种结果。如果并非如此，你怎样处理才能得到类似结果呢？

1. `_exit` 的目的是为进程提供一种 **无需运行终止处理程序或信号处理程序而终止的方法**；
2. `_exit` 是系统调用，而 exit 是标准库函数
3. 我们可以通过 close 或者 fclose 来手动的关闭 stdout，但是这会导致无法写入数据到终端；可以 exit(status)，随后 `echo $?` 获取 status

```c
#include "../apue.h"

int globvar = 6;

int main(int argc, char **argv)
{
    int var;
    pid_t pid;

    printf("before vfork\n");

    var = 88;
    if ((pid = vfork()) < 0) {
        err_sys("vfork error");
    } else if (pid == 0) {
        globvar++;
        var++;
        _exit(0);
    }

    close(STDOUT_FILENO);
    int pc = printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globvar, var);
    printf("print cnt = %d\n", pc);

    exit(pc);
}
```

### 8.3

>重写图8-6中的程序，把wait换成waitid。不调用pr_exit，而从siginfo结构中确定等价的信息。

1. si_signo contains the system-generated signal number. For the waitid(2) function, si_signo is always SIGCHLD.
2. If si_errno is non-zero, it contains an error number associated with this signal, as defined in <errno.h>.
3. si_code contains a code identifying the cause of the signal.
4. [Signal_codes](https://www.mkssoftware.com/docs/man5/siginfo_t.5.asp#Signal_Codes)

```c
#include "../apue.h"
#include "sys/wait.h"

void pr_exit_sig(const siginfo_t *sig)
{
    printf("signo: %d, code: %d\n", sig->si_signo, sig->si_code);
    if (WIFEXITED(sig->si_status))
        printf("normal termination");
    // signo: 20, code: 1
    printf("%d\n", WIFEXITED(sig->si_code));
    // 0
}

int main(int argc, char **argv)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        exit(7);

    siginfo_t sig;
    if (waitid(P_PID, pid, &sig, WEXITED) < 0)
        err_sys("waitid error");
    pr_exit_sig(&sig);
}

```
