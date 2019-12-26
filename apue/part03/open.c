#include <fcntl.h>
#include <errno.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int fd = open(__FILE__, O_RDONLY | O_CREAT);

    if (fd < 0)
        printf("open [%s] failed caused by %s\n", __FILE__, strerror(errno));
    else
        printf("open [%s]! fd = [%d]\n", __FILE__, fd);
}