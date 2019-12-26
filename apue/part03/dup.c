#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    char buf[MAXLINE];
    int fd  = open(__FILE__, O_RDONLY);
    int nfd = dup2(STDOUT_FILENO, fd);
    // fd = [3], nfd = [1]
    // write [20] char!
    sprintf(buf, "fd = [%d], nfd = [%d]\n", fd, nfd);
    if (write(nfd, buf, strlen(buf)) != strlen(buf))
    {
        printf("write error!");
    }
    else
    {
        printf("write [%lu] char!\n", strlen(buf));
    }
}