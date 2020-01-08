#include <errno.h>
#include "../apue.h"

int my_system(const char *cmdstring)
{
    pid_t pid;
    int   status = 0;

    if (cmdstring == NULL)
    {
        return (1);
    }

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        execl("/bin/sh", "sh", "-c", cmdstring, NULL);
        _exit(127);
    }
    else
    {
        while (waitpid(pid, &status, 0) < 0)
        {
            if (errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }

    return (status);
}

int main(int argc, char **argv)
{
    my_system(argv[1]);
}
