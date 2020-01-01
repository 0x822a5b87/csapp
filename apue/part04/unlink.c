#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    if (open("tempfile", O_RDONLY | O_CREAT) < 0)
        err_sys("open error");
    if (unlink("tempfile") < 0)
        err_sys("unlink error");
    printf("file unlinked\n");

    sleep(15);
    printf("done\n");
    exit(0);
}