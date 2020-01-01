#include "../apue.h"

int main(int argc, char **argv)
{
    char *ptr;
    int size;
    if (chdir("/Users/dhy/tmp") < 0)
        err_sys("chdir failed");
    ptr = (char *)path_alloc(&size);
    if (getcwd(ptr, size) == NULL)
        err_sys("getcwd failed");
    printf("cwd = %s\n", ptr);
    exit(0);
}