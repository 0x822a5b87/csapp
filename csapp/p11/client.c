#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "sys/socket.h"
#include "stdio.h"

int main(int argc, char **argv)
{
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0) {
        printf("create socket failed\n");
        return -1;
    }

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(argv[2]));
    struct in_addr ip;
    int            iton = inet_pton(AF_INET, argv[1], &ip);
    if (iton < 0) {
        printf("parse ip addr failed\n");
        return -2;
    }
    sa.sin_addr = ip;
    printf("addr = [%d], port = [%d]\n", sa.sin_addr.s_addr, sa.sin_port);

    int connectfd = connect(clientfd, (struct sockaddr *)&sa, sizeof(sa));
    if (connectfd == 0) {
        printf("connect successfully\n");
        exit(0);
    }
}