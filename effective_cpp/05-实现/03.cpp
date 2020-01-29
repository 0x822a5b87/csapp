#include "iostream"

inline int add(const int a, const int b)
{
    return a + b;
}

int add3(int a, int b, int c, int d, int e)
{
    int ret = add(a, b);
    ret = add(ret, c);
    ret = add(ret, d);
    ret = add(ret, e);

    return ret;
}
