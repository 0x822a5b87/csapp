#include "../apue.h"
#include "sys/wait.h"

void pr_exit_sig(const siginfo_t *sig)
{
    printf("signo: %d, code: %d\n", sig->si_signo, sig->si_code);
    // signo: 20, code: 1
    printf("signo == SIGCHLD: %d\n", sig->si_signo == SIGCHLD);
    // signo == SIGCHLD: 1
    printf("%d\n", sig->si_code == ILL_ILLTRP);
}

int main(int argc, char **argv)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        exit(7);

    siginfo_t sig;
    if (waitid(P_PID, pid, &sig, WEXITED) < 0)
        err_sys("waitid error");
    pr_exit_sig(&sig);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        abort();

    if (waitid(P_PID, pid, &sig, WEXITED) < 0)
        err_sys("waitid error");
    pr_exit_sig(&sig);
}
