#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include "../../apue.h"

int main(int argc, char **argv)
{
    char buf[PATH_MAX];
    char filename[PATH_MAX];
    int fd = open(argv[1], O_CREAT, S_IRWXU);
    if (fd < 0)
        err_sys("error open file :%s", argv[1]);

    int deep = 1;
    while (getcwd(buf, PATH_MAX) != NULL)
    {
        printf("current word dir: %s\n", buf);
        sprintf(filename, "%s%d", "dir", deep++);
        if (mkdir(filename, S_IRWXU))
            err_sys("error mkdir : %s", filename);
        if (chdir(filename) < 0)
            err_sys("error chdir : %s", filename);
    }
    printf("%s\n", strerror(errno));
    // Result too large
}