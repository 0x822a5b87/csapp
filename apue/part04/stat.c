#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int fd = open(__FILE__, O_RDONLY);

    // 注意，stat 中是不包含文件名的。因为 linux 中一个文件可以有多个文件名
    struct stat s;
    if (fstat(fd, &s) == -1)
        err_quit("failed fstat [%d]", __FILE__);

    char filePath[MAXLINE];
    if (fcntl(fd, F_GETPATH, filePath) != -1)
    {
        printf("file path = [%s]\n", filePath);
    }
}