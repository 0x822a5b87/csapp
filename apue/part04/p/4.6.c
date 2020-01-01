#include <fcntl.h>
#include "../../apue.h"

int cp(const char *path, const char *dst);

static int closefd(int fd);

int main(int argc, char **argv)
{
    cp(argv[1], argv[2]);
}

int cp(const char *path, const char *dst)
{
    int fd, dstfd;
    if ((fd = open(path, O_RDONLY)) < 0
        || (dstfd = open(dst, O_WRONLY)) < 0)
    {
        err_sys("error open path: %s", path);
        return -1;
    }

    char usrbuf[MAXLINE];
    size_t n;
    while ((n = read(fd, usrbuf, MAXLINE)) > 0)
    {
        for (size_t i = 0; i < n; ++i)
        {
            if (usrbuf[i] != 0)
            {
                ssize_t wn = write(dstfd, &usrbuf[i], 1);
            }
        }
    }

    closefd(fd);
    closefd(dstfd);

    return 0;
}


static int closefd(int fd)
{
    if (fd > 0)
        return close(fd);

    return -1;
}
