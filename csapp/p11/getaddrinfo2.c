#include <netdb.h>
#include "stdio.h"
#include "../csapp.hpp"

int main()
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;

    struct addrinfo addr;
    struct addrinfo *result = &addr;

    int ret = getaddrinfo("127.0.0.1", "8080", &hints, &result);
    if (ret < 0)
    {
        unix_error("error getaddrinfo\n");
        exit(0);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        unix_error("error create socket");
        exit(0);
    }

    int connfd = -1;
    for (struct addrinfo *start = result;
         start != NULL && connfd != 0;
         start = start->ai_next)
    {
        struct sockaddr    *aa = result->ai_addr;
        struct sockaddr_in *sa = (struct sockaddr_in *) aa;
        printf("addr = [%d], port = [%d]\n", sa->sin_addr.s_addr, sa->sin_port);
        connfd = connect(sockfd, aa, sizeof(*aa));
        if (connfd == 0)
        {
            printf("connect successfully\n");
        }
        else
        {
            printf("connect failed, connfd = [%d], errno = [%d]\n", connfd, errno);
        }
    }

    freeaddrinfo(result);
}