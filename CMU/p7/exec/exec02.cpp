//
// Created by 杜航宇 on 2019-10-25.
//

#include "iostream"
#include "exec01.cpp"

void add_global()
{
    ++local;
}

int main()
{
    self2();
    self();
    add_global();
    self();
}
