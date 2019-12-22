//
// Created by 杜航宇 on 2019-11-28.
//

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

    sleep(1);
    printf("parent: pid = [%d] : x = [%d]\n", getpid(), --x);
    exit(0);
}
