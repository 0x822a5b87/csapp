#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include <errno.h>

int main(int argc, char **argv)
{
    int fd;
    if (unlink(argv[1]) < 0)
    {
        printf("error unlink %s\n", argv[1]);
        printf("errno = %d\n", errno);
    }
    if ((fd = creat(argv[1], 0755)))
    {
        printf("error create file\n");
        printf("errno = %d\n", errno);
    }
}