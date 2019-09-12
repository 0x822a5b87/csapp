//
// Created by 杜航宇 on 2019-09-12.
//

#include "iostream"

/**
 * c[i][j] = a[i][0] * b[0][j] + ... + a[i][n] * b[n][j]
 *
 * 我们的缓存包含了 c 的写缓存和 a、b 的读缓存
 */

#define N 10

void matrix_mul(int n, int arr0[3][3], int arr1[3][3], int dest[3][3])
{
    for (int i = 0; i != n; ++i)
    {
        for (int j = 0; j != n; ++j)
        {
            int sum = 0;
            for (int k = 0; k != n; ++k)
            {
                sum += arr0[i][k] * arr1[k][j];
            }
            dest[i][j] = sum;
        }
    }
}

void matrix_mul2(int n, int arr0[3][3], int arr1[3][3], int dest[3][3])
{
    for (int k = 0; k != n; ++k)
    {
        for (int i = 0; i != n; ++i)
        {
            int r = arr0[i][k];
            for (int j = 0; j != n; ++j)
            {
                /**
                 * i 和 k 在内循环中都不变， 所以可以最大程度的利用缓存
                 */
                dest[i][j] += arr1[k][j] * r;
            }
        }
    }
}

int main()
{
    int arr0[3][3] = {{1, 2, 3},
                      {4, 5, 6},
                      {7, 8, 9}};
    int arr1[3][3] = {{1, 2, 3},
                      {4, 5, 6},
                      {7, 8, 9}};
    int dest[3][3] = {};
    matrix_mul(3, arr0, arr1, dest);
}
