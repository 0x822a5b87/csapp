//
// Created by 杜航宇 on 2019-11-28.
//

#include <zconf.h>
#include "iostream"

int main()
{
    // get proc id
    pid_t pid  = getpid();
    // get parent proc id
    pid_t ppid = getppid();
    std::cout << "pid = " << pid
              << ", ppid = " << ppid << std::endl;
}
