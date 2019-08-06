//
// Created by 杜航宇 on 2019-08-03.
//

#include "iostream"

void cond_goto(long a, long *p)
{
    if (p == nullptr)
        goto done;
    if (a <= *p)
        goto done;

    *p = a;
    done:
        return;
}
