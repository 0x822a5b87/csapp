//
// Created by 杜航宇 on 2019-11-28.
//

#include <zconf.h>
#include "iostream"

int main(int argc, char *argv[], char **env)
{
    printf("print pid = [%d]\n", getpid());
    std::cout << "argc = " << argc << std::endl;
    for(int i = 0; i < argc; ++i)
    {
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
    }
}
