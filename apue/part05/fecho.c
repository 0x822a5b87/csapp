#include "../apue.h"

#ifndef MAXLINE0
#define MAXLINE0 4
#endif

int main(int argc, char **argv)
{
    char buf[MAXLINE0];
    while(fgets(buf, MAXLINE0, stdin) != NULL)
    {
        fputs(buf, stdout);
        printf("echo: [%s]", buf);
        // hello
        // hello
        //
        // echo: [hello
        // ]
    }
}