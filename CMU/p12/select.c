#include "stdio.h"
#include "../csapp.hpp"

void command(void);
void echo(int connfd);

void print_fd_set(const fd_set *fs)
{
    size_t len = __DARWIN_howmany(__DARWIN_FD_SETSIZE, __DARWIN_NFDBITS);
    for(int i = 0; i != len; ++i)
    {
        printf("fs[%d] = [%d]\n", i, fs->fds_bits[i]);
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    int    listenfd, connfd;
    fd_set read_set, ready_set;
    struct sockaddr_storage sock;
    socklen_t socklen;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(listenfd, &read_set);

    while(1)
    {
        ready_set = read_set;
        Select(listenfd + 1, &ready_set, NULL, NULL, 0);
        if (FD_ISSET(STDIN_FILENO, &ready_set)) {
            printf("read from stdin\n");
            command();
        }
        if (FD_ISSET(listenfd, &ready_set)) {
            socklen = sizeof(sock);
            connfd = Accept(listenfd, (SA *) &sock, &socklen);
            echo(connfd);
            Close(connfd);
        }
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

void command(void)
{
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin)) {
        exit(0);
    }
    printf("%s", buf);
}