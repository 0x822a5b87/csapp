#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int fd = open("file.sync", O_WRONLY | O_CREAT);
    if (fd < 0)
    {
        err_sys("open file error");
    }
    if (fcntl(fd, F_SETFL, O_SYNC) < 0)
    {
        err_sys("fcntl error");
    }
}