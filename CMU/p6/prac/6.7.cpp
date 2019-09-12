//
// Created by 杜航宇 on 2019-09-11.
//

#include "iostream"

#define N 10

int sum_array_3d(int a[N][N][N])
{
    int i, j, k, sum = 0;

    for (i = 0; i != N; ++i)
    {
        for (k = 0; k != N; ++k)
        {
            for (j = 0; j != N; ++j)
            {
                sum += a[k][i][j];
            }
        }
    }

    return sum;
}
