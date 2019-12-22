//
// Created by 杜航宇 on 2019-11-28.
//

#include "iostream"
#include "../8.2/m_fork.cpp"

int main()
{
    int x = 1;

    if (Fork() == 0)
        printf("p1: x = %d\n", ++x);
    printf("p2: x = %d\n", --x);
}
