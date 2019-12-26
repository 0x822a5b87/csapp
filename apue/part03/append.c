#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int fd = open(__FILE__, O_WRONLY | O_CREAT | O_APPEND);

    char *buf = "\n//append test\n";
    off_t offset = lseek(fd, 0, SEEK_CUR);
    printf("append offset = %lld\n", offset);
    write(fd, buf, strlen(buf));
    offset = lseek(fd, 0, SEEK_SET);
    printf("after seek append offset = %lld\n", offset);
    write(fd, buf, strlen(buf));
}
//append test

//append test
