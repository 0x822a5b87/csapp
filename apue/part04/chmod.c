#include <fcntl.h>
#include "../apue.h"

#define RWRWRW (S_IRWXU|S_IRWXG|S_IRWXO)

int main(int argc, char **argv)
{
    struct stat s;
    int         mode = (s.st_mode & ~S_IXGRP) | S_ISGID;
    printf("mode = [%d]\n", mode);

    if (stat("foo", &s) < 0)
        err_sys("stat error for foo");
    if (chmod("foo", mode) < 0)
        err_sys("chmod error for foo");
    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
        err_sys("chmod error for bar");
}