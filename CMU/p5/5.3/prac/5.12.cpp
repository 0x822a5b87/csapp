//
// Created by 杜航宇 on 2019-09-10.
//

#include "iostream"

void psum1(const float a[], float p[], long n)
{
    long i;
    p[0] = a[0];
    for (i = 1; i != n; ++i)
    {
        p[i] = p[i - 1] + a[i];
    }
}

void psum2(const float a[], float p[], long n)
{
    float tmp = 0;
    for (int i = 0; i != n; ++i)
    {
        float i1 = tmp + a[i];
        p[i] = i1;
        tmp = i1;
    }
}

int main()
{
    float a[] = {1, 2, 3, 4, 5}, p[5] = {0, 0, 0, 0, 0};
    psum1(a, p, 5);

    for (int i = 0; i != 5; ++i)
    {
        std::cout << p[i] << " ";
    }
}