//
// Created by 杜航宇 on 2019-11-28.
//

#include "iostream"
#include "../8.2/m_fork.cpp"

#define N 10

int main()
{
    int   status, i;
    pid_t pid;

    for (i = 0; i < N; ++i)
    {
        if ((pid = Fork()) == 0)
        {
            exit(100 + i);
        }
    }
    // status 不等于进程调用 exit(n) 退出的值 n，而是包含了 n 这个值和退出状态等信息
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        //  WIFEXITED 提取退出状态，如果退出状态正常那么返回一个非零值
        if (WIFEXITED(status))
        {
            // WEXITSTATUS 提取 exit(n) 中的 n
            printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        }
        else
        {
            printf("child %d terminated abnormally\n", pid);
        }
    }

    if (errno != ECHILD)
    {
        unix_error("waitpid error");
    }

    exit(0);
}
