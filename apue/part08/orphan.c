#include "../apue.h"

int main(int argc, char **argv)
{
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        // child process
        printf("pid: %d\tppid:%d\n",getpid(),getppid());
        sleep(3);
        printf("pid: %d\tppid:%d\n",getpid(),getppid());
        printf("child process exit\n");
        exit(0);
    }
    else
    {
        // parent process
        printf("self_pid = %d, pid = %d\n", getpid(), pid);
        printf("parent process exit\n");
        exit(0);
    }

    // pubic statement
}