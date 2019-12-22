//
// Created by 杜航宇 on 2019/11/30.
//

#include "iostream"
#include "../../../csapp.hpp"

volatile sig_atomic_t pid;

void sigchld_handler(int sig)
{
    int olderrno = errno;
    pid = waitpid(-1, NULL, 0);
    errno = olderrno;
}

int main()
{
    sigset_t mask, prev;
    Signal(SIGCHLD, sigchld_handler);

    Sigemptyset(&mask);
    Sigaddset(&mask, SIGCHLD);

    while (1)
    {
        Sigprocmask(SIG_BLOCK, &mask, &prev);
        if (Fork() == 0)
        {
            sleep(1);
            exit(0);
        }
        pid = 0;
        Sigprocmask(SIG_SETMASK, &prev, NULL);
        while(!pid)
        {

        }
        printf(".\n");
    }
}
