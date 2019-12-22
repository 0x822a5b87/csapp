#include "stdio.h"
#include "../csapp.cpp"

void echo(int connfd);

void *thread(void *args);

int main(int argc, char **argv)
{
    // 注意，我们这里分配的是一个 int * 指向了 connfd。
    // 如果不这么做的话将会有并发问题，因为所有的线程共享了一个 connfd
    int                     listenfd, *connfd;
    struct sockaddr_storage addr;
    socklen_t               socklen;
    pthread_t tid;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1)
    {
        socklen = sizeof(addr);
        connfd = (int *)Malloc(sizeof(int));
        *connfd = Accept(listenfd, (SA *) &addr, &socklen);
        pthread_create(&tid, NULL, thread, connfd);
    }
}

void *thread(void *args)
{
    int connfd = *((int *) args);
    Pthread_detach(Pthread_self());
    echo(connfd);
    Close(connfd);
    Free(args);
    return NULL;
}

void echo(int connfd)
{
    char  buf[MAXLINE];
    rio_t rio;
    Rio_readinitb(&rio, connfd);
    printf("begin read\n");
    ssize_t n;
    while ((n = Rio_readlineb(&rio, buf, RIO_BUFSIZE)) != 0)
    {
        if (strstr(buf, "quit!"))
        {
            printf("quit!\n");
            exit(0);
        }
        printf("read message : [%s], cnt = [%lu]\n", buf, n);
        Rio_writen(connfd, buf, n);
    }
}

