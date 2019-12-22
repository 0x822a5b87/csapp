//
// Created by 杜航宇 on 2019-08-22.
//

#include "iostream"

// 原始函数
long sum(long *start, long count)
{
    if (count <= 0)
    {
        return 0;
    }
    return *start + sum(start + 1, count - 1);
}

int main()
{
    long arr[] = {1, 2, 3, 4, 5 };
    sum(arr, 5);
}
