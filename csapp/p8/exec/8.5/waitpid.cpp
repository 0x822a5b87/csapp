//
// Created by 杜航宇 on 2019/12/2.
//

#include <zconf.h>
#include "iostream"
#include "../../../csapp.hpp"

int main()
{
    pid_t pid, ppid;

    if ((pid = Fork()) == 0)
    {
        sleep(1);
        exit(0);
    }

    if ((ppid = Fork()) == 0)
    {
        sleep(1);
        exit(0);
    }

    int status;
    while (Waitpid(pid, &status, WUNTRACED) < 0)
    {
        printf("wait pid 1\n");
    }
    while (Waitpid(pid, &status, WUNTRACED) < 0)
    {
        printf("wait pid 2\n");
    }
}
