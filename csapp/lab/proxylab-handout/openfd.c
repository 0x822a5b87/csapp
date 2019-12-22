#include "csapp.h"

int main(int argc, char **argv)
{
    char src[MAXLINE], dst[MAXLINE];
    strcpy(src, "http://localhost:18342/home.html");
    strcpy(dst, "/home.html");
    strcpy(src, dst);
//    const char text[] = "http://localhost:8080/tiny.c\n\r";
//    char ip[100];
//    char port[100];
//    char page[100];
//    sscanf(text, "http://%99[^:]:%99[^/]%99[^\n]", ip, port, page);
//    printf("ip = \"%s\"\n", ip);
//    printf("port = \"%s\"\n", port);
//    printf("page = \"%s\"\n", page);
//
//    struct addrinfo addr;
//    struct addrinfo *result = &addr;
//
//    Getaddrinfo(ip, port, NULL, &result);
//    int clientfd = Open_clientfd(ip, port);
//    printf("clientfd = [%d]\n", clientfd);
//
//    rio_t rio;
//    char usrbuf[MAXLINE];
//    Rio_readinitb(&rio, clientfd);
//    char *buf = "GET /home.html HTTP/1.1\n\r\n\r\n";
//    Rio_writen(clientfd, buf, strlen(buf));
//    size_t n;
//
//    while ((n = Rio_readlineb(&rio, usrbuf, MAXLINE)) > 0)
//    {
//        printf("%s", usrbuf);
//    }
//    printf("n = [%zu]\n", n);
}
