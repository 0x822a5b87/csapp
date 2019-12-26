#include <fcntl.h>
#include "../apue.h"

off_t Lseek(int, off_t, int);

int main(int argc, char **argv)
{
    int fd = open(__FILE__, O_CREAT | O_RDONLY);
    if (fd < 0)
        return -1;

    off_t offset = Lseek(fd, 0, SEEK_CUR);
    printf("current offset = %lld\n", offset);
    offset = Lseek(fd, 0, SEEK_END);
    printf("end offset = %lld\n", offset);

    offset = Lseek(fd, -offset, SEEK_END);
    printf("start offset = %lld\n", offset);
}


off_t Lseek(int fd, off_t offset, int mode)
{
    off_t cur_off;
    if ((cur_off = lseek(fd, offset, mode)) == -1)
    {
        exit(-1);
    }
    return cur_off;
}
