#include "../apue.h"

static void sig_cld(int);

int main(int argc, char **argv)
{
    pid_t pid;

#ifdef SIGCLD
    if (signal(SIGCHLD, sig_cld) == SIG_ERR)
        err_sys("signal error");
#endif
    if ((pid = fork()) < 0) {
        perror("signal error");
    } else if (pid == 0) {
        sleep(2);
        _exit(0);
    }

    pause();
    exit(0);
}

static void sig_cld(int signo)
{
    pid_t pid;
    int status;
    printf("SIGCLD received\n");

#ifdef SIGCLD
    if (signal(SIGCLD, sig_cld) == SIG_ERR)
        err_sys("signal error");
#endif
    if ((pid = wait(&status)) < 0)
        perror("wait error");

    printf("pid = %d\n", pid);
}