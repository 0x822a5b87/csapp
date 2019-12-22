//
// Created by 杜航宇 on 2019-11-28.
//

#include "iostream"
#include "../8.2/m_fork.cpp"

int main()
{
    if (Fork() == 0)
    {
        printf("a");
        fflush(stdout);
    }
    else
    {
        printf("b");
        fflush(stdout);
        waitpid(-1, nullptr, 0);
    }

    printf("c");
    fflush(stdout);
    exit(0);
}
