#include <time.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    char buf[MAXLINE];
    if (strftime(buf, MAXLINE, "%a %b %d %H %M %S %Z %Y", timeinfo) < 0)
        err_sys("strftime error");

    printf("%s\n", buf);
}