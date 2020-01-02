#include "../apue.h"

void my_setbuf(FILE * __restrict, char * __restrict);

int main(int argc, char **argv)
{
}

void my_setbuf(FILE * __restrict fp, char * __restrict buf)
{
    if (buf == NULL)
        setvbuf(fp, NULL, _IONBF, 0);
    else
        setvbuf(fp, buf, _IOFBF, BUFSIZ);
}
