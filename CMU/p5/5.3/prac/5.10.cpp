//
// Created by 杜航宇 on 2019-09-10.
//

#include "iostream"

void copy_array(long *src, long *dest, long n)
{
    for (long i = 0; i != n; ++i)
    {
        dest[i] = src[i];
    }
}

int main()
{
    long arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    copy_array(arr, arr + 1, 9);

    for (const long &num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}