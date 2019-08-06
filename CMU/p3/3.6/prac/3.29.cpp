//
// Created by 杜航宇 on 2019-08-04.
//

#include "iostream"

int ch03_3_29()
{
    long sum = 0;
    long i = 0;
    goto test;
    statement:
    if (i & 0x1)
    {
        i++;
        goto test;
    }
        sum += i;
        i++;
    test:
    if (i < 10)
        goto statement;

    return sum;
}

int ch03_3_29_answer()
{
    long sum = 0;
    long i = 0;
    while (i < 10)
    {
        if (i & 0x1)
        {
            goto update;
        }
        sum += i;
update:
        ++i;
    }

    return sum;
}

int main()
{
    std::cout << ch03_3_29() << std::endl;
}
