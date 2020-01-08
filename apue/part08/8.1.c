#include "../apue.h"

int globvar = 6;

int main(int argc, char **argv)
{
    int var;
    pid_t pid;

    printf("before vfork\n");

    var = 88;
    if ((pid = vfork()) < 0) {
        err_sys("vfork error");
    } else if (pid == 0) {
        globvar++;
        var++;
        _exit(0);
    }

    close(STDOUT_FILENO);
    int pc = printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globvar, var);
    printf("print cnt = %d\n", pc);

    exit(pc);
}