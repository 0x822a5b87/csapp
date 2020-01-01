#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        err_quit("usage: a.out <pathname>");

    // fd == AT_FDCWD 时与 access 权限一致
    if (faccessat(AT_FDCWD, argv[1], R_OK, AT_EACCESS) < 0)
        err_ret("access error for %s", argv[1]);
    else
        printf("read access OK\n");

    if (open(argv[1], O_RDONLY) < 0)
        err_ret("open error for %s", argv[1]);
    else
        printf("open for reading OK\n");

    return 0;
}