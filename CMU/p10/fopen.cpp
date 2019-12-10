//
// Created by 杜航宇 on 2019/12/10.
//

#include <printf.h>
#include <zconf.h>
#include "fcntl.h"

int main()
{
    int fd = open("./fopen.cpp", O_RDONLY | O_APPEND);
    printf("fd = [%d]\n", fd);
    close(fd);
}