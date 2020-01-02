#include <sys/time.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    time_t t = time(NULL);
    printf("%ld\n", t);
    // 1577966439

    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) < 0)
        err_sys("clock_gettime error");

    printf("%ld/%ld\n", ts.tv_sec, ts.tv_nsec);
    // 1577967112/479804000
}