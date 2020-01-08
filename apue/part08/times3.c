#include <stdio.h>
#include <sys/times.h>

int main()
{
    struct tms t;
    clock_t t2 = times(&t);
    printf("t = %lu\n", t2);

    return 0;
}