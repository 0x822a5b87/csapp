#include "../apue.h"

int initialized_global = 10;
int uninitialized_global;
int initialized_global2 = 10;
int uninitialized_global2;

int main(int argc, char **argv)
{
    int static_uninitialized;
    int static_uninitialized2;
    int static_initialized = 10;
    int static_initialized2 = 10;

    printf("&initialized_global    = %p\n", &initialized_global);
    printf("&initialized_global2   = %p\n", &initialized_global2);
    printf("&uninitialized_global  = %p\n", &uninitialized_global);
    printf("&uninitialized_global2 = %p\n", &uninitialized_global2);

    printf("&static_initialized    = %p\n", &static_initialized);
    printf("&static_initialized2   = %p\n", &static_initialized2);
    printf("&static_uninitialized  = %p\n", &static_uninitialized);
    printf("&static_uninitialized2 = %p\n", &static_uninitialized2);
}