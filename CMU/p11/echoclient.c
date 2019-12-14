#include <netinet/tcp.h>
#include "stdio.h"
#include "../csapp.hpp"

int main(int argc, char **argv)
{
    int  clientfd;
    char *host = argv[1], *port= argv[2], buf[MAXLINE];
    rio_t rio;

    clientfd = Open_clientfd(host, port);
    if (clientfd < 0) {
        unix_error("error open client fd\n");
    }

    Rio_readinitb(&rio, clientfd);

    while (Fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        Fputs(buf, stdout);
    }

    exit(0);
}