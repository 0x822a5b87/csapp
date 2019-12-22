#include "stdio.h"
#include "../csapp.hpp"

void echo(int connfd);

void chld_sighandler(int sig)
{
    printf("chld_sighandler\n");
    int status;
    // 再回忆一下为什么要使用 while 循环
    //
    while((waitpid(-1, &status, WNOHANG)) > 0)
        ;

    printf("end chld_sighandler\n");
}

int main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_storage addr;
    socklen_t socklen;
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    Signal(SIGCHLD, chld_sighandler);
    listenfd = Open_listenfd(argv[1]);
    while (1)
    {
        connfd = Accept(listenfd, (SA *) &addr, &socklen);
        if (Fork() == 0)
        {
            Close(listenfd);
            echo(connfd);
            Close(connfd);
            printf("child close connfd\n");
            exit(0);
        }

        Close(connfd);
    }
}

void echo(int connfd)
{
    char buf[MAXLINE];
    rio_t rio;
    Rio_readinitb(&rio, connfd);
    printf("begin read\n");
    ssize_t n;
    while ((n = Rio_readlineb(&rio, buf, RIO_BUFSIZE)) != 0) {
        if (strstr(buf, "quit!")) {
            printf("quit!\n");
            exit(0);
        }
        printf("read message : [%s], cnt = [%lu]\n", buf, n);
        Rio_writen(connfd, buf, n);
    }
}
