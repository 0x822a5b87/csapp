#include <fcntl.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    char cwd[MAXLINE];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }

    struct stat s;
    if (stat(cwd, &s) == -1)
        err_quit("stat err");

    if (S_ISDIR(s.st_mode))
    {
        printf("%s is dir file", cwd);
    }

    return 0;
}