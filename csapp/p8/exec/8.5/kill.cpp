//
// Created by 杜航宇 on 2019/11/29.
//
#include <iostream>
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
        std::cout << getppid() << " " <<getpid() << std::endl;
        //Pause();
        //printf("control should never reach here");
        //exit(0);
        kill(getpid(), SIGINT);
    }

    if (pid != 0)
    {
        std::cout << "pid = " << getpid() << " sleep for 1 sec." << std::endl;
        sleep(1);
    }
    std::cout << "pid = " << getpid() << " submit SIGKILL" << std::endl;
    // Parent sends a SIGKILL signal to a child
    Kill(pid, SIGINT);

    exit(0);
}
