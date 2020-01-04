#include "../apue.h"

int f(int ret)
{
    return ret;
}

int main(int argc, char **argv)
{
    f(atoi(argv[1]));
}