//
// Created by 杜航宇 on 2019-11-28.
//

#include <zconf.h>
#include "iostream"

void unix_error(const char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}


pid_t Fork()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        unix_error("Fork error");
    }

    return pid;
}
