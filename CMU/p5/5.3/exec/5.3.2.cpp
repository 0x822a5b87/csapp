//
// Created by 杜航宇 on 2019-09-05.
//

#include "iostream"
#include "sys/time.h"

void copy_array(long *src, long *dest, long n)
{
    for (long i = 0; i != n; ++i)
    {
        dest[i] = src[i];
    }
}

void run_copy_array(long cnt, long *src, long *dest, long n)
{
    for (size_t i = 0; i != cnt; ++i)
    {
        copy_array(src, dest, n);
    }
}

#define M 10
#define N 10

void sum_array_rows(int a[M][N])
{
    int i, j, sum = 0;
    for (i = 0; i != M; ++i)
        for (j = 0; j != N; ++j)
            sum += a[i][j];
}

void sum_array_cols(int a[M][N])
{
    int i, j, sum = 0;
    for (j = 0; j != N; ++j)
        for (i = 0; i != M; ++i)
            sum += a[i][j];
}

void sum_n(long cnt, int arr[M][N], void (*sum_arr)(int [M][N]))
{
    for (int i = 0; i != cnt; ++i)
    {
        sum_arr(arr);
    }
}


int main()
{

    unsigned cnt = 0xffffff;

    using namespace std::chrono;
    milliseconds start, end;

    long arr1[] = {1,2,3,4,5,6,7,8,9,0};
    int arr[M][N] = {};
    for (int i = 0; i != M; ++i)
    {
        for (int j = 0; j != N; ++j)
        {
            arr[i][j] = i * 10 + j;
        }
    }

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    sum_n(cnt, arr, sum_array_rows);
    end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    std::cout << (end - start).count() << std::endl;

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    sum_n(cnt, arr, sum_array_cols);
    end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    std::cout << (end - start).count() << std::endl;

}
