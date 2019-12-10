//
// Created by 杜航宇 on 2019/12/10.
//

#include "iostream"
#include "../csapp.hpp"

int main()
{
    int n;
    rio_t rio;
    char buf[MAXLINE];

    Rio_readinitb(&rio, STDIN_FILENO);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        Rio_writen(STDOUT_FILENO, buf, n);
    }
}
