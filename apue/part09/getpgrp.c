#include "../apue.h"

int main(int argc, char **argv)
{
    pid_t pgid = getpgrp();
    pid_t pid  = getpid();
    pid_t pgid2 = getpgid(pid);
    printf("pgid = %ld, pgid2 = %ld, pid = %d\n", ((long) pgid), ((long) pgid2), pid);
}