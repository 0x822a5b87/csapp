#include <limits.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    id_t id       = getpid();
    int  priority = getpriority(PRIO_PROCESS, id);
    printf("pri = %d\n", priority);

    int nzero = NZERO;
    nzero = nice(10);
    printf("nice(10) = %d\n", nzero);

    priority = getpriority(PRIO_PROCESS, id);
    printf("after nice(10), pri = %d\n", priority);

    nzero = nice(0);
    printf("nice(0) = %d\n", nzero);

    priority = getpriority(PRIO_PROCESS, id);
    printf("after nice(0) = %d\n", priority);

}