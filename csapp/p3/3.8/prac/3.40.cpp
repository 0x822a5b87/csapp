//
// Created by 杜航宇 on 2019-08-08.
//

#include "iostream"

#define N 16

typedef int fix_matrix[N][N];

void fix_set_diag_opt(fix_matrix A, int val)
{
    long i = 0;
    int *ptr = &A[0][0];
    do
    {
        *(ptr + i) = val;
        i += (N + 1);
    } while (i < (4 * N * (N + 1)));
}

void fix_set_diag_opt_answer(fix_matrix A, int val)
{
    long i = 0;
    long end = N * (N + 1);
    int *ptr = &A[0][0];
    do
    {
        *(ptr + i) = val;
        i += (N + 1);

    } while (i != end);
}

