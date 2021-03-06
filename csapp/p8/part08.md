# 异常控制流

1. ECF 发生在计算器系统的各个层次
2. C++，Java 之类的语言的异常是一种应用层的 ECF，在 C 中是通过 setjmp 和 longjmp 函数提供的。

## 8.1 异常

1. 在处理器中，状态被编码为不同的位和信号。状态变化称之为 `事件`
2. 当处理器检测到有 `事件` 发生时，会通过 `异常表` 的跳转表进行一次间接过程调用，到一个专门设计来处理这类事件的操作系统子程序

### 8.1.1 异常处理

1. 每个异常都分配了一个非负整数的异常号
2. 在操作系统启动时，会初始化一个异常表，table[k] -> 异常 k 的处理程序
3. 在运行时，处理器检测到了一个事件并确定了异常的编号 k，就可以去调用 table[k] 的处理程序

### 8.2.2  异常的类别

1. 中断：例如键盘的输入就属于一种硬件中断，它是异步的；
2. trap 和系统调用：系统调用会导致一个到异常处理程序的 trap，这个处理程序解析参数，并调用适当的内核程序
3. 故障：故障可能会跳转到一个程序去试图修复故障，修复成功则跳回到引起故障的指令，否则执行 abort 退出程序。例如缺页异常就是一个典型的故障。
4. 终止：终止是不可恢复的致命故障引起的，一般是硬件错误

## 8.2 进程

1. 异常为我们进程的实现提供了可能；
2. 进程提供了独立的逻辑控制流，好像我们的进程独占处理器；
3. 进程提供了私有的地址空间，好像我们的程序独占使用内存系统；

### 8.2.4 用户模式和内核模式

1. 处理器通过一个寄存器的模式来控制，当设置了这个标志位之后，进程就运行在内核态中 -- 可以执行指令集中的所有指令，访问内存中的任意位置
2. linux 可以通过 `/proc` 来访问内核数据结构的内容

## 8.4 进程控制

1. 使用 `fork()` 可以创建新的进程，新进程得到父进程用户级的虚拟空间相同并且独立的一份副本，包括代码和数据段、堆、共享库以及用户栈。
2. `fork()` 只会调用一次，但是会返回两次。一次在父进程中，返回子进程的 pid，一次在子进程中，返回父进程的 pid

```c++
#include "iostream"
#include "../8.2/m_fork.cpp"

int main()
{
    pid_t pid;
    int   x = 1;
    printf("parent: pid = [%d]\n", getpid());

    pid = Fork();
    if (pid == 0)
    {
        printf("child : pid = [%d] : x = [%d]\n", getpid(), ++x);
    }

    printf("parent: pid = [%d] : x = [%d]\n", getpid(), --x);
    exit(0);
}
```

>parent: pid = [60828]
>parent: pid = [60828] : x = [0]
>child : pid = [60829] : x = [2]
>parent: pid = [60829] : x = [1]

## 8.5 信号

```c++
#include <signal.h>

typedef void (*sighandler_t) (int)

sighandler_t signal(int signum, sighandler_t handler);
```

1. 一个信号就是一条消息，可能是进程自身发给自身的，也有可能是从其他的进程传递过来的；
2. 信号有很多不同的类型，例如 SIGINT, SIGQUIT, SIGSYS

### 8.5.1 信号术语

1. 可以通过 `kill()` 命令向指定进程或进程组发送信号
2. 信号的接收是强制的，但是我们可以通过 `signal()` 来指定当我们收到某一个信号时的处理程序
3. 一个信号被发出而没有被接收的信号叫做待处理（pending）信号。一个种类的信号至多只会有一个待处理信号。例如，假设我连续的发送三个 SIGINT，并且后面两个 SIGINT 在第一个 SIGINT 接收但处理程序处理完之前发出。那么只有两个 SIGINT 会被处理，因为第二个 SIGINT 被当做待处理信号，而第三个 SIGINT 则被丢弃了
4. 在 <3> 中说的这个特征，是因为内核是以 bitmap 的形式维护 SIGINT 的，所以没有办法保存多个信号。

### 8.5.2 发送信号

1. unix 提供了大量向进程发送信号的机制，这些机制都是基于信号组实现的
2. 在代码中，我们一般通过 `kill()` 来向进程或者进程组发送信号

### 8.5.3 接收信号

1. 当内核把进程 p 从 **内核模式切换到用户模式时(从系统调用中返回，或者完成了一次上下文切换)**，它会检查进程 p 的 `未被阻塞` 的待处理信号的集合 (`pending & !blocked`)
2. 如果 <1> 中检查的集合不为空，那么 **内核选择一个信号并且强制进程接收，从执行代码逻辑跳转到执行异常处理程序**
3. 可以通过 `signal(int signum, sighandler_t handler)` 来指定某个异常对应的异常处理程序

### 8.5.4 阻塞和接触阻塞信号

1. 信号存在隐式阻塞机制，比如当程序在处理 SIGINT 的信号时，又接受到一个 SIGINT 信号，那么第二个到达的信号就被隐式的阻塞了
2. 我们也可以显式的来阻塞某些信号，具体的方式就是更新信号的 bitmap，那么自然收到的信号就被阻塞了
3. `sigprocmask(how, set, oldset)` 函数可以用来 **修改当前阻塞的信号集**。
    1.1 SIG_BLOCK 将 set 添加到当前信号集，并且将原来的信号集存储到 oldset
    1.2 SIG_UNBLOCK 将 set 从当前信号集删除，并且将原来的信号存储到 oldset
    1.3 SIG_SETMASK 直接设置当前信号集为 set
4. 我们可以利用这个特性，来避免出现并发问题。

### 8.5.5 编写信号处理程序

1. 处理程序与主程序是并发执行的，有可能在主程序执行到某一个时间节点时突然接收到一个信号，然后跳转到信号处理程序中。
2. 我们可以通过 `sigprocmask` 来阻塞某些信号。例如当我们手动阻塞了 SIGINT 后，如果我们再接收一个 SIGINT 信号，那么 SIGINT 会被放到 pending 中而不是跳转到处理程序
3. 对于全局变量，我们需要通过 volatile 声明。这样可以保证每次都从内存中加载而不是使用寄存器中的缓存数据。
4. 用 sig_atomic_t 来声明标志。再常见的处理程序设计中，我们可能会写全局标志来记录收到的信号。
5. **未处理的信号不排队，** 每个信号最多只会有一个未处理信号。关键思想在于，如果存在一个未处理信号就表名至少有一个信号达到了。

### 8.5.6 同步流以避免讨厌的并发错误

1. 由于主程序和异常处理程序是并发的执行的，他们可能会出现并发问题；
2. 解决问题的思路就是：**在信号可能产生之前，我们必须手动的去阻塞这个信号。并且在某个合适的节点（例如访问完共享数据之后）取消对这个信号的阻塞**。例如，我们使用 SIGCHLD 信号来在子进程执行完毕之后将子进程从列表中删除，那么当我们调用 fork() 的那一瞬间开始，我们的信号就有可能被发出。所以我们必须要在调用 fork() 之前去阻塞这个 SIGCHLD 信号.

### 8.5.7 显式的等待信号

1. 可以使用 `sigsuspend()` 函数来手动的等待信号
2. `sigsuspend(mask)` 相当于原子三条指令：
    2.1 sigprocmask(SIG_SETMASK, mask, prev);
    2.2 pause()
    2.3 sigprocmask(SIG_SETMASK, prev NULL);
3. <2> 相当于先阻塞 mask 指定的指令，并且等待信号，当信号激活 pause() 后，将信号集还原到调用 sigsuspend 之前的状态
4. 但是 pause() 会响应所有的信号，所以我们必须在 sigprocmask 激活之后判断信号是否为我们的目标信号。这个通常是通过判断 `sig_atomic_t` 标志位来实现的。例如，如果我们等待的是 SIGINT 信号，那么我们可以在 SIGINT 信号中修改标志位。当我们从 sigprocmask 激活之后判断这个标志位的状态来确定 SIGINT 的处理函数是否执行。并且在下一次等待 SIGINT 信号之前将标志位设置为未执行的状态。























