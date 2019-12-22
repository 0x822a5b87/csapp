//
// Created by 杜航宇 on 2019/12/10.
//

#include <zconf.h>
#include "iostream"
#include "../csapp.hpp"

void rio_readintb(rio_t *rp, int fd);

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);

ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n, nread = 0;
    char   *bufp = (char *) usrbuf;

    while (nleft > 0)
    {
        if ((nread = read(fd, bufp, n)) < 0)
        {
            if (errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if (nread == 0)
        {
            return nread;
        }
        else
        {
            nleft -= nread;
            bufp += nread;
        }
    }

    return (n - nleft);
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n, nwrite = 0;
    char   *bufp = (char *) usrbuf;

    while (nleft > 0)
    {
        if ((nwrite = (write(fd, bufp, nleft))) <= 0)
        {
            if (errno == EINTR)
                nwrite = 0;
            else
                return -1;
        }
        else
        {
            nleft -= nwrite;
            bufp += nwrite;
        }
    }
    return n;
}
