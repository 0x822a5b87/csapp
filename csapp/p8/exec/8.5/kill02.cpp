//
// Created by 杜航宇 on 2019/11/29.
//

#include <zconf.h>
#include "iostream"
#include "../../../csapp.hpp"

void caught_signal_handler(int sig)
{
    printf("pid = [%d] caught signal [%d]\n", getpid(), sig);
}

int main()
{
    pid_t pid;
    printf("parent pid = [%d]\n", getpid());

    if (signal(SIGINT, caught_signal_handler) == SIG_ERR)
    {
        unix_error("signal error");
    }

    if ((pid = Fork()) == 0)
    {
        printf("pid [%d] send SIGINT to [%d]\n", getpid(), getpid());
        kill(getpid(), SIGINT);
    }
    sleep(1);
}
