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

int main()
{
    unsigned cnt = 0xfffffff;

    using namespace std::chrono;
    milliseconds start, end;

    long arr1[] = {1,2,3,4,5,6,7,8,9,0};

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    run_copy_array(cnt, arr1, arr1 + 1, 9);
    end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    std::cout << (end - start).count() << std::endl;

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    run_copy_array(cnt, arr1, arr1, 9);
    end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    std::cout << (end - start).count() << std::endl;
}
