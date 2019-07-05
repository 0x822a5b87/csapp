#include "stdio.h"

typedef struct
{
    int a[2];
    double d;
} struct_t;

double func(int i)
{
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 1073741824;

    return s.d;
}

int main()
{
    printf("%f\n", func(0));
    printf("%f\n", func(1));
    printf("%f\n", func(2));
    printf("%f\n", func(3));
    printf("%f\n", func(4));
    printf("%f\n", func(5));
    printf("%f\n", func(6));
    // 3.140000
    // 3.140000
    // 3.140000
    // 2.000001
    // 3.140000
    // 3.140000
    // 3.140000
    // [1]    3735 segmentation fault  ./a.out

    return 0;
}