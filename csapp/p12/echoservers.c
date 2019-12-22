#include "stdio.h"
#include "../csapp.cpp"

typedef struct
{
    int    maxfd;
    fd_set ready_set;
    fd_set read_set;
    int    nready;
    int    maxi;
    int    clientfd[FD_SETSIZE];
    rio_t  clientrio[FD_SETSIZE];
} pool;

int byte_cnt = 0;

void init_pool(int listenfd, pool *p);

void add_client(int connfd, pool *p);

void check_clients(pool *p);

int main(int argc, char **argv)
{
    int                     listenfd, connfd;
    struct sockaddr_storage addr;
    socklen_t               clientlen;
    static pool             p;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, &p);

    while (1)
    {
        p.ready_set = p.read_set;
        // 监听连接
        p.nready    = Select(p.maxfd + 1, &p.ready_set, NULL, NULL, NULL);
        if (FD_ISSET(listenfd, &p.ready_set))
        {
            clientlen = sizeof(addr);
            connfd    = Accept(listenfd, (SA *) &addr, &clientlen);
            add_client(connfd, &p);
        }
        check_clients(&p);
    }
}


void check_clients(pool *p)
{
    int   i, connfd, n;
    char  buf[MAXLINE];
    rio_t rio;

    for (i = 0; (i <= p->maxi && p->nready > 0); ++i)
    {
        connfd = p->clientfd[i];
        rio    = p->clientrio[i];

        if (connfd > 0 && FD_ISSET(connfd, &p->ready_set))
        {
            if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
            {
                byte_cnt += n;
                printf("read [%d] message [%s]\n", n, buf);
                Rio_writen(connfd, buf, n);
            }
            else
            {
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}

void add_client(int connfd, pool *p)
{
    int i;
    p->nready--;
    for (i = 0; i < FD_SETSIZE; i++)
    {
        if (p->clientfd[i] < 0)
        {
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);

            FD_SET(connfd, &p->read_set);
            if (connfd > p->maxfd)
                p->maxfd = connfd;
            // 更新 maxi，这样 check_client 就不需要更新整个数组了
            if (i > p->maxi)
                p->maxi  = i;

            break;
        }
    }
    if (i == FD_SETSIZE)
        app_error("add_client error: Too many clients");
}

void init_pool(int listenfd, pool *p)
{
    p->maxi    = -1;
    for (int i = 0; i < FD_SETSIZE; i++)
    {
        p->clientfd[i] = -1;
    }

    p->maxfd = listenfd;
    FD_SET(listenfd, &p->read_set);
    FD_ZERO(&p->ready_set);
    p->nready = 0;
}