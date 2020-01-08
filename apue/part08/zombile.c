#include "../apue.h"

int main(int argc, char **argv)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
        err_sys("fork error");
    pid_t ppid = getpid();
    if (pid == 0)
    {
        // child process
        printf("child  process, pid = %d, ppid = %d\n", getpid(), getppid());
        printf("child  process exit without waitpid\n");
        exit(0);
    }
    else
    {
        // parent process
        printf("parent process, pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(1);
        char buf[MAXLINE];
        sprintf(buf, "ps -o pid,ppid,state,tty,command | grep %d", pid);
        system(buf);
    }
}