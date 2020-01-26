#include "../apue.h"

int main(int argc, char **argv)
{
    pid_t pid;
    pid_t pgrpid;

    if ((pid = fork()) == 0)
    {
        pgrpid = getpgrp();
        printf("child pid = %ld, pgrpid = %ld\n",(long) getpid(), (long) pgrpid);
    }
    else
    {
        pgrpid = getpgrp();
        printf("parent pid = %ld, pgrpid = %ld\n", (long) getpid(), (long) pgrpid);
    }
}