//
// Created by 杜航宇 on 2019/11/30.
//

#include <zconf.h>
#include "../../../csapp.hpp"

volatile int sig_int_cnt = 0;

void sig_int_handler(int sig)
{
    ++sig_int_cnt;
    printf("sig int is running, sig_int_cnt = [%d]\n", sig_int_cnt);
    sleep(1);
}

int main()
{
    Signal(SIGINT, sig_int_handler);
    pid_t pid, ppid;
    int status = 0;
    ppid = getpid();
    if ((pid = fork()) == 0)
    {
        for (int i = 0; i < 100; ++i)
        {
            Kill(ppid, SIGINT);
        }
        sleep(5);
    }

    if (getpid() == ppid)
    {
        Waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            printf("the process terminated normally by a call to _exit(2) or exit(3).\n");
        }
    }
}

