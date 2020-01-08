#include "../apue.h"

int main(int argc, char **argv)
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        if (execl("/Users/dhy/code/hangyudu/csapp/apue/part08/testinterp",
                  "testinterp", "myarg1", "MY ARG2", NULL) < 0)
        {
            err_sys("execl error");
        }
    }

    if (waitpid(pid, NULL, 0) < 0)
    {
        err_sys("waitpid error");
    }

    exit(0);
}