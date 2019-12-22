//
// Created by 杜航宇 on 2019-11-28.
//

#include "iostream"

int main(int argc, char *argv[], char *env[])
{
    printf("CommandLine arguments:\n");
    for (int i = 0; i < argc; ++i)
    {
        printf("\targ[%2d] = %s\n", i, argv[i]);
    }

    printf("Environment variables:\n");
    if (env != nullptr)
    {
        for (int i = 0; env[i] != nullptr; ++i)
        {
            printf("\tenv[%2d] = %s\n", i, env[i]);
        }
    }
}
