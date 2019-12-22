//
// Created by 杜航宇 on 2019/11/29.
//

#include <zconf.h>
#include "../../../csapp.hpp"

void sig_sys_handler(int sig)
{
    printf("pid = [%d] Caught SIGINT [%d]!\n", getpid(), sig);
    Kill(getpid(), SIGINT);
}

void sig_int_handler(int sig)
{
    printf("pid = [%d] Caught SIGINT [%d]!\n", getpid(), sig);
}

int main()
{
    Signal(SIGSYS, sig_sys_handler);
    Signal(SIGINT, sig_int_handler);

    Kill(getpid(), SIGSYS);
}
