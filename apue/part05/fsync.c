#include "../apue.h"

int main(int argc, char **argv)
{
    FILE *fp = stdout;
    int  fd  = fileno(fp);
    printf("stdin fd = %d\n", fd);
}