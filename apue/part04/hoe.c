#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int fd = open("file.hoe", O_RDWR | O_TRUNC | O_CREAT, 0755);
    if (fd == -1)
        err_sys("open file error");
    ssize_t wn = write(fd, "hello world", 11);
    printf("write cnt %zd\n", wn);

    off_t offset = lseek(fd, 0, SEEK_SET);
    printf("offset = %lld\n", offset);
    char    buf[MAXLINE];
    ssize_t rn   = read(fd, buf, MAXLINE);
    // 下面这样输出是错误的
    // printf("read cnt %zd, buf = %s\n", rn, buf);
    offset = lseek(fd, 1024, SEEK_END);
    printf("offset = %lld\n", offset);
    wn = write(fd, "hello world", 11);
    printf("write cnt %zd\n", wn);

    offset = lseek(fd, 0, SEEK_SET);
    printf("offset = %lld\n", offset);
    rn = read(fd, buf, MAXLINE);
    printf("read cnt %zd, buf = %s\n", rn, buf);
    struct stat s;
}