#include <fcntl.h>
#include "../../apue.h"

int main(int argc, char **argv)
{
    int fd = open("non_exit_file", O_RDONLY);

    perror("open non_exit_file");
    fd = open("errno.c", O_RDONLY);

    printf("fd = %d\n", fd);
    perror("open errno.c");
    // open non_exit_file: No such file or directory
    // fd = 3
    // open errno.c: No such file or directory
}