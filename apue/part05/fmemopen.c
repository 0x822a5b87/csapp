#include <stdio.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    char buf[BUFSIZ];
    memset(buf, '\0', 1);
    strcpy(buf + 1, "hello world");
    FILE *fp = fmemopen(buf, BUFSIZ, "r");
    if (fp == NULL)
        err_sys("fmemopen error");
    fputs(buf, fp);

    printf("[%s]\n", buf);

    char usrbuf[BUFSIZ];
    if (fgets(usrbuf, BUFSIZ, fp) == NULL)
        err_sys("fgets to usrbuf error");
    printf("[%s]\n", usrbuf);
    // []

    fseek(fp, 0, SEEK_SET);
    if (fgets(usrbuf, BUFSIZ, fp) == NULL)
        err_sys("fgets to usrbuf error");
    printf("[%s]\n", usrbuf);
    // [hello world]
    fclose(fp);

    fp = fmemopen(buf, BUFSIZ, "a");
    printf("buf = [%s]\n", buf);
    if (fputs(" from APUE!", fp) == EOF)
        err_sys("fputs error");
    printf("buf = [%s]\n", buf);
    // buf = [hello world from APUE!]
    fseek(fp, 0, SEEK_SET);
    if (fputs("hello world again!", fp) == EOF)
        err_sys("fputs error");
    printf("buf = [%s]\n", buf);
    // buf = [hello world from APUE!hello world again!]
    fseek(fp, 0, SEEK_SET);
    memset(buf, '\0', BUFSIZ);
    if (fputs("hello world again!", fp) == EOF)
        err_sys("fputs error");
    printf("buf = [%s]\n", buf);
    for (int i = 0; i < BUFSIZ; ++i)
    {
        printf("%c", buf[i]);
    }
    // (n NULL)hello world again!(other NULL)
}