#include "../apue.h"
#include <stdlib.h>

typedef void (*Exitfunc)(void);

void my_atexit(Exitfunc);

void my_exit(void);

int main(int argc, char **argv)
{
    my_atexit(my_exit);
    atexit(my_exit);
}

void my_atexit(Exitfunc exitfunc)
{
    exitfunc();
}

void my_exit(void)
{
    printf("hello world from my_exit!\n");
}
