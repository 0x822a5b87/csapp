#include <stdio.h>
#include "../apue.h"

FILE *my_fmemopen(void * restrict buf, size_t size, const char * restrict mode)
{
    return NULL;
}

int my_write(void *buf, const char *s, int n)
{
    fputs("my_write", stdout);
    return 0;
}

int main(int argc, char **argv)
{
    FILE *fp = funopen(stdout, read, my_write, lseek, fclose);
    if (fp == NULL)
        err_sys("error funopen");

    if (fputs("hello world", fp) < 0)
        err_sys("err fputs");

    fputs("fputs", stdout);
}