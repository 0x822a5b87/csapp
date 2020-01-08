#include <sys/times.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    struct tms t;
    clock_t ct = times(&t);
    if (ct < 0)
        err_sys("times error");

    int i = 0, zero = 0;
    while (i++ < 10000)
    {
        printf("cnt = %d\n", i);
    }

    printf("collapse time = [%lu]\n", ct);
    printf("user time = %lu, system time = %lu\n", t.tms_utime, t.tms_stime);
    printf("terminated children : user time = %lu, system time = %lu\n", t.tms_utime, t.tms_stime);
}