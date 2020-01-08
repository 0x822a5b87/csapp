#include "../apue.h"

int main(int argc, char **argv)
{
    char *v[10];
    v[1] = "-A";
    if (execvp("ls", v) < 0)
        err_sys("execlp error");
}