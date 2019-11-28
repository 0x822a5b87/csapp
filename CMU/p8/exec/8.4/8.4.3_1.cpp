//
// Created by 杜航宇 on 2019-11-28.
//

#include <zconf.h>
#include "iostream"

int main()
{
    int x = 0;
    printf("parent: pid = [%d]\n", getpid());
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("child : pid = [%d]\n", getpid());
    }
    else
    {
        pid_t m_pid = waitpid(pid, &x, 0);
        printf("waitpid return [%d]\n", m_pid);
    }

    printf("pid [%d] exit!\n", getpid());
}
