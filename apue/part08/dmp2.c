#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int f0 = open(__FILE__, O_RDONLY);
    off_t f = lseek(f0, 0, SEEK_END);
    printf("f = %lld, after seek = %lld\n", f, lseek(f0, 0, SEEK_CUR));
    dup2(f0, STDIN_FILENO);
    f = lseek(STDIN_FILENO, 0, SEEK_END);
    printf("f = %lld, after seek = %lld\n", f, lseek(f0, 0, SEEK_CUR));
}