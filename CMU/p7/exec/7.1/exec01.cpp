//
// Created by 杜航宇 on 2019-10-25.
//

#include "iostream"

static int global = 0;
int        local  = 0;

static void self2()
{
    std::cout << "in exec01.cpp, global = " << global
              << ", local = " << local << std::endl;
}

void self()
{
    std::cout << "in exec01.cpp, global = " << global
              << ", local = " << local << std::endl;
}
