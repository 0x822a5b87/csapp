#include "../apue.h"

int main(int argc, char **argv)
{
    char buf[12];
    size_t n;
    if ((n = sprintf(buf, "%s %s", "hello", "world")) < 0)
        err_sys("sprintf error: %d", n);

    printf("%zu: %s", n, buf);
}