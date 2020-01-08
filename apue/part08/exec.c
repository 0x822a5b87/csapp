#include "../apue.h"

int main(int argc, char **argv)
{
    if (execlp("ls", "-A", NULL) < 0)
        err_sys("execlp error");
}