//
// Created by 杜航宇 on 2019-08-08.
//

#include "iostream"

struct ELE {
    long v;
    struct ELE *p;
};

long fun(struct ELE *ptr)
{
    long ret = 0;
    while (ptr != nullptr)
    {
        ret += ptr->v;
        ptr = ptr->p;
    }
    return ret;
}
