//
// Created by 杜航宇 on 2019/11/29.
//

#include "iostream"
#include "../../../csapp.hpp"

void sigint_handler(int sig)
{
    printf("Caught SIGINT!\n");
    exit(0);
}

int main()
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        unix_error("signal error");
    }

    Pause();

    return 0;
}