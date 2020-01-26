#include <zconf.h>
#include <signal.h>
#include <pwd.h>
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "../apue.h"

static void my_alarm(int signo)
{
    struct passwd *rootptr;
    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL)
    {
        printf("exit\n");
        exit(0);
    }
    printf("getpwnam(root)\n");
    alarm(1);
}

static void my_seg(int signo)
{
    printf("segment fault\n");
}

int main(int argc, char **argv)
{
    struct passwd *ptr;
    signal(SIGALRM, my_alarm);
    signal(SIGSEGV, my_seg);
    alarm(1);
    for(;;)
    {
        if ((ptr = getpwnam("dhy")) == NULL)
        {
            err_sys("getpwnam('dhy') error");
            exit(0);
        }
        if (strcmp(ptr->pw_name, "dhy") != 0)
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
    }
}