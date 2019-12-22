//
// Created by 杜航宇 on 2019/11/30.
//

#include "../../../csapp.cpp"

// 这个程序是由缺陷的，因为它假设信号是排队的
// 我们发现，虽然发送了三个信号给父进程，但是有一个进程没有备正常回收
void handler1(int sig)
{
    int olderrorno = errno;
    if((waitpid(-1, NULL, 0)) < 0)
    {
        sio_error("waitpid error");
    }
    Sio_puts("Handler reaped child\n");
    Sleep(1);
    errno = olderrorno;
}

// 这个程序可以解决信号不会排队的问题
// 1. 我们将 if 修改为了 while，因为 waitpid 是阻塞直到有任意一个进程退出
void handler2(int sig)
{
    int olderrno = errno;

    // 只要进入这个函数，必然有至少一个子进程结束
    while(waitpid(-1, NULL, 0) > 0)
    {
        Sio_puts("Handler reaped child\n");
    }
    if (errno != ECHILD)
    {
        Sio_error("waitpid error");
    }

    Sio_puts("step into handler2\n");

    errno = olderrno;
}

int main()
{
    int i, n;
    char buf[MAXBUF];
    Signal(SIGCHLD, handler2);
    for (i = 0; i < 9; ++i)
    {
        if (Fork() == 0)
        {
            printf("Hello from child [%d]\n", getpid());
            exit(0);
        }
    }

    // 注意，我们并不会非常快的执行到这一句。
    // 因为，当我们在 for 循环中执行的时候，由于有子进程退出，所以会被中断并跳转到异常处理程序
    Sio_puts("parent process start read!\n");
    if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
    {
        unix_error("read");
    }

    printf("Parent processing input\n");
    while(1)
    {

    }

    exit(0);
}
