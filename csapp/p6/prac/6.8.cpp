//
// Created by 杜航宇 on 2019-09-11.
//

#include "iostream"

#define N 100

typedef struct
{
    int vel[3];
    int acc[3];
} point;

void clear1(point *p, int n)
{
    for (int i = 0; i != n; ++i)
    {
        for (int j = 0; j != n; ++j)
        {
            p[i].vel[j] = 0;
        }
        for (int j = 0; j != n; ++j)
        {
            p[i].acc[j] = 0;
        }
    }
}

void clear2(point *p, int n)
{
    for (int i = 0; i != n; ++i)
    {
        for (int j = 0; j != n; ++j)
        {
            p[i].vel[j] = 0;
            p[i].acc[j] = 0;
        }
    }

}

