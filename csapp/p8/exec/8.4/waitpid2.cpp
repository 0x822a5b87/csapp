//
// Created by 杜航宇 on 2019-11-28.
//

#include "iostream"
#include "../8.2/m_fork.cpp"

#define N 10

int main()
{
    int i, status;
    pid_t pids[N], retpid;

    for (i = 0; i < N; ++i)
    {
        if ((pids[i] = Fork()) == 0)
        {
            exit(100 + i);
        }
    }

    for (i = 0; i < N; ++i)
    {
        retpid = waitpid(pids[i], &status, 0);
        if (WIFEXITED(status))
        {
            // WEXITSTATUS 提取 exit(n) 中的 n
            printf("child %d terminated normally with exit status=%d\n", retpid, WEXITSTATUS(status));
        }
        else
        {
            printf("child %d terminated abnormally\n", retpid);
        }
    }

    if (errno != ECHILD)
    {
        unix_error("waitpid error");
    }

    exit(0);
}
