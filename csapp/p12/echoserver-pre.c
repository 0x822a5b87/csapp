#include "../csapp.h"
#include "sbuf.h"

#define NTHREADS 4
#define SBUFSIZE 16

void echo_cnt(int connfd);

void *thread(void *);

sbuf_t sbuf;

int main(int argc, char **argv)
{
    int i, listenfd, connfd;
    struct sockaddr_storage addr;
    socklen_t socklen;
    pthread_t tid;
    
    if (argc != 2)
    {
        printf("usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);

    sbuf_init(&sbuf, SBUFSIZE);
    for (i = 0; i < NTHREADS; ++i)
    {
        Pthread_create(&tid, NULL, thread, NULL);
    }

    while(1)
    {
        socklen = sizeof(addr);
        connfd = Accept(listenfd, (SA *) &addr, &socklen);
        sbuf_insert(&sbuf, connfd);
    }
}

void *thread(void *args)
{
    // 这个必不可少
    Pthread_detach(pthread_self());
    while(1)
    {
        int connfd = sbuf_remove(&sbuf);
        echo_cnt(connfd);
        Close(connfd);
    }
}