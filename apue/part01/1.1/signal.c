#include <errno.h>
#include "../../apue.h"

static void sig_int(int);

int main(int argc, char **argv)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if(buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if ((pid = fork()) < 0)
        {
            perror("fork");
            strerror(errno);
        }
        else if (pid == 0)
        {
            execlp(buf, buf, (char *) 0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        printf("%% ");
    }

    exit(0);
}

void sig_int(int sig)
{
    printf("interrupt!\n%%");
}
