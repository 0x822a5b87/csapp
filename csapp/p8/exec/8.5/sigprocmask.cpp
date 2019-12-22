//
// Created by 杜航宇 on 2019/11/30.
//

#include "iostream"
#include "../../../csapp.hpp"

int main()
{
    sigset_t mask, prev;

    Sigemptyset(&mask);
    Sigemptyset(&prev);

    printf("mask = [%d], prev = [%d]\n", mask, prev);

    Sigaddset(&mask, SIGINT);
    printf("mask = [%d], prev = [%d]\n", mask, prev);

    Sigprocmask(SIG_BLOCK, &mask, &prev);
    printf("mask = [%d], prev = [%d]\n", mask, prev);

    Sigaddset(&mask, SIGSYS);
    Sigprocmask(SIG_BLOCK, &mask, &prev);
    printf("mask = [%d], prev = [%d]\n", mask, prev);
}
