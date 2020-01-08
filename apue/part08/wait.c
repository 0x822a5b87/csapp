#include <errno.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int pcnt = 0, realcnt = atoi(argv[1]), status;

    for (int i = 0; i < atoi(argv[1]); ++i)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            exit(0);
        }
        else if (pid < 0)
        {
            perror(strerror(errno));
        }
    }

    while (wait(&status) != -1)
    {
        ++pcnt;
    }

    printf("realcnt = %d, pcnt = %d\n", realcnt, pcnt);
}